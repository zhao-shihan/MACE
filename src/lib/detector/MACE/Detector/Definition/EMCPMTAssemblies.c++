#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

#include "fmt/format.h"

#include <algorithm>
#include <cassert>
#include <utility>

namespace MACE::Detector::Definition {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

auto EMCPMTAssemblies::Construct(G4bool checkOverlaps) -> void {
    const auto& emc{Description::EMC::Instance()};
    const auto name{emc.Name()};
    // const auto nSubdivision{emc.NSubdivision()};
    const auto& faceList{emc.Mesh().fFaceList};
    const auto& typeMap{emc.Mesh().fTypeMap};

    const auto pmtDimensions{emc.PMTDimensions()};

    const auto pmtCouplerThickness{emc.PMTCouplerThickness()};
    const auto pmtWindowThickness{emc.PMTWindowThickness()};
    const auto pmtCathodeThickness{emc.PMTCathodeThickness()};

    const auto pmtWaveLengthBin{emc.PMTWaveLengthBin()};
    const auto pmtQuantumEfficiency{emc.PMTQuantumEfficiency()};

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager{G4NistManager::Instance()};
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};
    const auto potassiumElement{nistManager->FindOrBuildElement("K")};
    const auto antimonyElement{nistManager->FindOrBuildElement("Sb")};
    const auto cesiumElement{nistManager->FindOrBuildElement("Cs")};

    const auto siliconeGrease{new G4Material("siliconeGrease", 1.06_g_cm3, 4, kStateLiquid)};
    siliconeGrease->AddElement(carbonElement, 2);
    siliconeGrease->AddElement(hydrogenElement, 6);
    siliconeGrease->AddElement(oxygenElement, 1);
    siliconeGrease->AddElement(siliconElement, 1);

    const auto glass{nistManager->FindOrBuildMaterial("G4_GLASS_PLATE")};
    const auto bialkali{new G4Material("Bialkali", 2.0_g_cm3, 3, kStateSolid)};
    bialkali->AddElement(potassiumElement, 2);
    bialkali->AddElement(cesiumElement, 1);
    bialkali->AddElement(antimonyElement, 1);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair{h_Planck * c_light / fLambdaMax,
                                            h_Planck * c_light / fLambdaMin};

    const auto siliconeGreasePropertiesTable{new G4MaterialPropertiesTable};
    siliconeGreasePropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.46, 1.46}); // EJ-550
    siliconeGreasePropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {100_cm, 100_cm});
    siliconeGrease->SetMaterialPropertiesTable(siliconeGreasePropertiesTable);

    const auto windowPropertiesTable{new G4MaterialPropertiesTable};
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.49, 1.49}); // ET 9269B 9956B
    glass->SetMaterialPropertiesTable(windowPropertiesTable);

    std::vector<G4double> cathodeSurfacePropertiesEnergy(pmtWaveLengthBin.size());
    std::vector<G4double> cathodeSurfacePropertiesEfficiency(pmtQuantumEfficiency.size());
    std::transform(pmtWaveLengthBin.begin(), pmtWaveLengthBin.end(), cathodeSurfacePropertiesEnergy.begin(),
                   [](auto val) { return h_Planck * c_light / (val * nm / mm); });
    std::transform(pmtQuantumEfficiency.begin(), pmtQuantumEfficiency.end(), cathodeSurfacePropertiesEfficiency.begin(),
                   [](auto n) { return n * perCent; });

    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", fEnergyPair, {1., 1.});
    // cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);

    if (Env::VerboseLevelReach<'V'>()) {
        cathodeSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    for (int unitID{};
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face

        if (unitID != 0) {
            unitID++;
            continue;
        }

        double pmtDiameter{};
        double cathodeDiameter{};
        double pmtLength{};

        auto typeMapIt = typeMap.find(unitID);
        pmtDiameter = pmtDimensions.at(typeMapIt->second).at(0);
        cathodeDiameter = pmtDimensions.at(typeMapIt->second).at(1);
        pmtLength = pmtDimensions.at(typeMapIt->second).at(2);
        // std::cout << "unitID: " << unitID << ", typeID:" << typeMapIt->second << ", pmtDiameter: " << pmtDiameter << ", cathodeDiameter: " << cathodeDiameter << ", pmtLength: " << pmtLength << std::endl;

        const auto couplerTransform{emc.ComputeTransformToOuterSurfaceWithOffset(unitID,
                                                                                 pmtCouplerThickness / 2)};

        const auto shellTransform{emc.ComputeTransformToOuterSurfaceWithOffset(unitID,
                                                                               pmtCouplerThickness + pmtLength / 2)};

        const auto cathodeTransform{emc.ComputeTransformToOuterSurfaceWithOffset(unitID,
                                                                                 pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2)};

        const auto solidCoupler{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtCouplerThickness / 2, 0, 2 * pi)};
        const auto logicCoupler{Make<G4LogicalVolume>(solidCoupler, siliconeGrease, "EMCPMTCoupler")};
        const auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                       logicCoupler,
                                                       "EMCPMTCoupler",
                                                       Mother().LogicalVolume(),
                                                       true,
                                                       unitID,
                                                       checkOverlaps)};

        // const auto solidGlassBox{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtLength / 2, 0, 2 * pi)};
        // const auto solidPMTVacuum{Make<G4Tubs>("temp", 0, pmtDiameter / 2 - pmtWindowThickness, pmtLength / 2 - pmtWindowThickness, 0, 2 * pi)};
        // const auto solidPMTShell{Make<G4SubtractionSolid>("EMCPMTShell", solidGlassBox, solidPMTVacuum)};
        // const auto logicPMTShell{Make<G4LogicalVolume>(solidPMTShell, glass, "EMCPMTShell")};
        // Make<G4PVPlacement>(shellTransform,
        //                     logicPMTShell,
        //                     "EMCPMTShell",
        //                     Mother().LogicalVolume(),
        //                     true,
        //                     unitID,
        //                     checkOverlaps);

        // const auto solidCathode{Make<G4Tubs>("temp", 0, cathodeDiameter / 2, pmtCathodeThickness / 2, 0, 2 * pi)};
        // const auto logicCathode{Make<G4LogicalVolume>(solidCathode, bialkali, "EMCPMTCathode")};
        // Make<G4PVPlacement>(cathodeTransform,
        //                     logicCathode,
        //                     "EMCPMTCathode",
        //                     Mother().LogicalVolume(),
        //                     true,
        //                     unitID,
        //                     checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        // const auto emcCrystal{FindSibling<EMCCrystal>()};
        // if (emcCrystal) {
        //     const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
        //     new G4LogicalBorderSurface{"couplerSurface",
        //                                emcCrystal->PhysicalVolume(fmt::format("EMCCrystal_{}", unitID)),
        //                                physicalCoupler,
        //                                couplerSurface};
        //     couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        // }

        const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"couplerSkinSurface", logicCoupler, couplerSurface};
        couplerSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        // const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
        // new G4LogicalSkinSurface{"cathodeSkinSurface", logicCathode, cathodeSurface};
        // cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        ++unitID;
    }
}

} // namespace MACE::Detector::Definition
