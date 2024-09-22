#include "MACE/Detector/Definition/ECalCrystal.h++"
#include "MACE/Detector/Definition/ECalMPPC.h++"
#include "MACE/Detector/Description/ECal.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

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

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;
using namespace Mustard::PhysicalConstant;

auto ECalMPPC::Construct(G4bool checkOverlaps) -> void {
    const auto& eCal{Description::ECal::Instance()};
    const auto name{eCal.Name()};
    const auto& faceList{eCal.Mesh().fFaceList};
    const auto& typeMap{eCal.Mesh().fTypeMap};

    const auto mppcWidthSet{eCal.MPPCWidthSet()};
    const auto mppcThickness{eCal.MPPCThickness()};
    const auto mppcCouplerThickness{eCal.MPPCCouplerThickness()};
    const auto mppcWindowThickness{eCal.MPPCWindowThickness()};

    const auto mppcWaveLengthBin{eCal.MPPCWaveLengthBin()};
    const auto mppcEfficiency{eCal.MPPCEfficiency()};

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager{G4NistManager::Instance()};
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};

    const auto silicon = nistManager->FindOrBuildMaterial("G4_Si");

    const auto siliconeGrease{new G4Material("siliconeGrease", 1.06_g_cm3, 4, kStateLiquid)};
    siliconeGrease->AddElement(carbonElement, 2);
    siliconeGrease->AddElement(hydrogenElement, 6);
    siliconeGrease->AddElement(oxygenElement, 1);
    siliconeGrease->AddElement(siliconElement, 1);

    const auto epoxy = new G4Material("epoxy", 1.18_g_cm3, 3, kStateSolid);
    epoxy->AddElement(carbonElement, 0.7362);
    epoxy->AddElement(hydrogenElement, 0.0675);
    epoxy->AddElement(oxygenElement, 0.1963);

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
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.57, 1.57});
    epoxy->SetMaterialPropertiesTable(windowPropertiesTable);

    std::vector<G4double> mppcSurfacePropertiesEnergy(mppcWaveLengthBin.size());
    std::vector<G4double> mppcSurfacePropertiesEfficiency(mppcEfficiency.size());
    std::transform(mppcWaveLengthBin.begin(), mppcWaveLengthBin.end(), mppcSurfacePropertiesEnergy.begin(),
                   [](auto val) { return h_Planck * c_light / (val * nm / mm); });
    std::transform(mppcEfficiency.begin(), mppcEfficiency.end(), mppcSurfacePropertiesEfficiency.begin(),
                   [](auto n) { return n * perCent; });

    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

    const auto mppcSurfacePropertiesTable{new G4MaterialPropertiesTable};
    mppcSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    mppcSurfacePropertiesTable->AddProperty("EFFICIENCY", mppcSurfacePropertiesEnergy, mppcSurfacePropertiesEfficiency);

    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        mppcSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    for (int moduleID{};
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all ECal face
        auto typeMapIt = typeMap.find(moduleID);
        double mppcWidth{mppcWidthSet.at(typeMapIt->second)};

        const auto couplerTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                 mppcCouplerThickness / 2)};

        const auto windowTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                mppcCouplerThickness + mppcWindowThickness / 2)};

        const auto cathodeTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                 mppcCouplerThickness + mppcWindowThickness + mppcThickness / 2)};

        const auto solidCoupler{Make<G4Box>("temp", mppcWidth / 2, mppcWidth / 2, mppcCouplerThickness / 2)};
        const auto logicCoupler{Make<G4LogicalVolume>(solidCoupler, siliconeGrease, "ECalMPPCCoupler")};
        const auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                       logicCoupler,
                                                       "ECalMPPCCoupler",
                                                       Mother().LogicalVolume(),
                                                       true,
                                                       moduleID,
                                                       checkOverlaps)};

        const auto solidWindow{Make<G4Box>("temp", mppcWidth / 2, mppcWidth / 2, mppcWindowThickness / 2)};
        const auto logicWindow{Make<G4LogicalVolume>(solidWindow, epoxy, "ECalMPPCWindow")};
        Make<G4PVPlacement>(windowTransform,
                            logicWindow,
                            "ECalMPPCWindow",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        const auto solidMPPC{Make<G4Box>("temp", mppcWidth / 2, mppcWidth / 2, mppcThickness / 2)};
        const auto logicMPPC{Make<G4LogicalVolume>(solidMPPC, silicon, "ECalMPPC")};
        Make<G4PVPlacement>(cathodeTransform,
                            logicMPPC,
                            "ECalMPPC",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto eCalCrystal{FindSibling<ECalCrystal>()};
        if (eCalCrystal) {
            const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
            new G4LogicalBorderSurface{"couplerSurface",
                                       eCalCrystal->PhysicalVolume(fmt::format("ECalCrystal_{}", moduleID)),
                                       physicalCoupler,
                                       couplerSurface};
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        const auto cathodeSurface{new G4OpticalSurface("MPPC", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"mppcSkinSurface", logicMPPC, cathodeSurface};
        cathodeSurface->SetMaterialPropertiesTable(mppcSurfacePropertiesTable);

        ++moduleID;
    }
}

} // namespace MACE::Detector::Definition
