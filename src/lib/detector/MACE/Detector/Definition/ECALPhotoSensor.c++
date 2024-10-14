#include "MACE/Detector/Definition/ECALCrystal.h++"
#include "MACE/Detector/Definition/ECALPhotoSensor.h++"
#include "MACE/Detector/Description/ECAL.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

#include "G4AssemblyVolume.hh"
#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VPVParameterisation.hh"

#include "fmt/format.h"

#include <algorithm>
#include <cassert>
#include <utility>

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;
using namespace Mustard::PhysicalConstant;

auto ECALPhotoSensor::Construct(G4bool checkOverlaps) -> void {
    if (Detector::Description::ECAL::Instance().UseMPPC()) {
        ConstructMPPC(checkOverlaps);
    } else {
        ConstructPMT(checkOverlaps);
    }
}

auto ECALPhotoSensor::ConstructMPPC(G4bool checkOverlaps) -> void {

    const auto& ecal{Description::ECAL::Instance()};
    const auto name{ecal.Name()};

    const auto mppcNPixelRows{ecal.MPPCNPixelRows()};
    const auto mppcPixelSizeSet{ecal.MPPCPixelSizeSet()};
    const auto mppcPitch{ecal.MPPCPitch()};
    const auto mppcThickness{ecal.MPPCThickness()};
    const auto mppcCouplerThickness{ecal.MPPCCouplerThickness()};
    const auto mppcWindowThickness{ecal.MPPCWindowThickness()};

    const auto mppcWaveLengthBin{ecal.MPPCWaveLengthBin()};
    const auto mppcEfficiency{ecal.MPPCEfficiency()};

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

    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", mppcSurfacePropertiesEnergy, mppcSurfacePropertiesEfficiency);

    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        cathodeSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////
    const auto& faceList{ecal.Mesh().fFaceList};
    const auto& typeMap{ecal.Mesh().fTypeMap};

    for (int moduleID{};
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all ECAL face
        auto typeMapIt = typeMap.find(moduleID);
        int mppcNPixelRow{mppcNPixelRows.at(typeMapIt->second)};
        double mppcPixelSize{mppcPixelSizeSet.at(typeMapIt->second)};
        const auto mppcWidth{mppcNPixelRow * (mppcPixelSize + mppcPitch) + mppcPitch};
        const auto couplerTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  mppcCouplerThickness / 2)};

        const auto windowTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                 mppcCouplerThickness + mppcWindowThickness / 2)};

        const auto cathodeTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  mppcCouplerThickness + mppcWindowThickness + mppcThickness / 2)};

        const auto solidCoupler{Make<G4Box>("temp", mppcWidth / 2, mppcWidth / 2, mppcCouplerThickness / 2)};
        const auto logicCoupler{Make<G4LogicalVolume>(solidCoupler, siliconeGrease, "ECALMPPCCoupler")};
        const auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                       logicCoupler,
                                                       "ECALMPPCCoupler",
                                                       Mother().LogicalVolume(),
                                                       true,
                                                       moduleID,
                                                       checkOverlaps)};

        // change volume window from epoxy to epoxy&silicon Pixels, may change name "window" later
        const auto solidWindow{Make<G4Box>("temp", mppcWidth / 2, mppcWidth / 2, mppcWindowThickness / 2)};
        const auto logicWindow{Make<G4LogicalVolume>(solidWindow, epoxy, "ECALMPPCWindow")};

        const auto solidPixel{Make<G4Box>("temp", mppcPixelSize / 2, mppcPixelSize / 2, mppcThickness / 2)};
        const auto logicPixel{Make<G4LogicalVolume>(solidPixel, silicon, "ECALPMCathode")};
        auto assemblyMPPC{new G4AssemblyVolume()};
        for (int copyNo = 0; copyNo < mppcNPixelRow * mppcNPixelRow; copyNo++) {
            int rowNum{copyNo / mppcNPixelRow};
            int colNum{copyNo % mppcNPixelRow};
            double xOffSet{(2 * rowNum + 1 - mppcNPixelRow) * ((mppcPixelSize + mppcPitch) / 2)};
            double yOffset{(2 * colNum + 1 - mppcNPixelRow) * ((mppcPixelSize + mppcPitch) / 2)};
            double zOffset{(mppcWindowThickness - mppcThickness) / 2};
            G4Transform3D Tr{G4Transform3D(G4RotationMatrix::IDENTITY, G4ThreeVector(xOffSet, yOffset, zOffset))};
            assemblyMPPC->AddPlacedVolume(logicPixel, Tr);
        }
        G4Transform3D transformInWindow{G4Transform3D(G4RotationMatrix::IDENTITY, G4ThreeVector(0, 0, 0))};
        assemblyMPPC->MakeImprint(logicWindow, transformInWindow);

        Make<G4PVPlacement>(windowTransform,
                            logicWindow,
                            "ECALMPPCWindow",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto ecalCrystal{FindSibling<ECALCrystal>()};
        if (ecalCrystal) {
            const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
            new G4LogicalBorderSurface{"couplerSurface",
                                       ecalCrystal->PhysicalVolume(fmt::format("ECALCrystal_{}", moduleID)),
                                       physicalCoupler,
                                       couplerSurface};
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"cathodeSkinSurface", logicPixel, cathodeSurface};
        cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        ++moduleID;
    }
}

auto ECALPhotoSensor::ConstructPMT(G4bool checkOverlaps) -> void {

    const auto& ecal{Description::ECAL::Instance()};
    const auto name{ecal.Name()};

    const auto pmtCouplerThickness{ecal.PMTCouplerThickness()};
    const auto pmtWindowThickness{ecal.PMTWindowThickness()};
    const auto pmtCathodeThickness{ecal.PMTCathodeThickness()};

    const auto pmtWaveLengthBin{ecal.PMTWaveLengthBin()};
    const auto pmtQuantumEfficiency{ecal.PMTQuantumEfficiency()};

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
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);

    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        cathodeSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    const auto& faceList{ecal.Mesh().fFaceList};
    const auto& typeMap{ecal.Mesh().fTypeMap};
    const auto& pmtDimensions{ecal.PMTDimensions()};
    for (int moduleID{};
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all ECAL face


        auto typeMapIt = typeMap.find(moduleID);
        auto pmtDiameter = pmtDimensions.at(typeMapIt->second).at(0);
        auto cathodeDiameter = pmtDimensions.at(typeMapIt->second).at(1);
        auto pmtLength = pmtDimensions.at(typeMapIt->second).at(2);

        const auto couplerTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  pmtCouplerThickness / 2)};

        const auto shellTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                pmtCouplerThickness + pmtLength / 2)};

        const auto cathodeTransform{ecal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2)};

        const auto solidCoupler{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtCouplerThickness / 2, 0, 2 * pi)};
        const auto logicCoupler{Make<G4LogicalVolume>(solidCoupler, siliconeGrease, "ECALPMTCoupler")};
        const auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                       logicCoupler,
                                                       "ECALPMTCoupler",
                                                       Mother().LogicalVolume(),
                                                       true,
                                                       moduleID,
                                                       checkOverlaps)};

        const auto solidGlassTube{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtLength / 2, 0, 2 * pi)};
        const auto solidPMTVacuum{Make<G4Tubs>("temp", 0, pmtDiameter / 2 - pmtWindowThickness, pmtLength / 2 - pmtWindowThickness, 0, 2 * pi)};
        const auto solidPMTShell{Make<G4SubtractionSolid>("ECALPMTShell", solidGlassTube, solidPMTVacuum)};
        const auto logicPMTShell{Make<G4LogicalVolume>(solidPMTShell, glass, "ECALPMTShell")};
        Make<G4PVPlacement>(shellTransform,
                            logicPMTShell,
                            "ECALPMTShell",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        const auto solidCathode{Make<G4Tubs>("temp", 0, cathodeDiameter / 2, pmtCathodeThickness / 2, 0, 2 * pi)};
        const auto logicCathode{Make<G4LogicalVolume>(solidCathode, bialkali, "ECALPMCathode")};
        Make<G4PVPlacement>(cathodeTransform,
                            logicCathode,
                            "ECALPMCathode",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////
        const auto ecalCrystal{FindSibling<ECALCrystal>()};
        if (ecalCrystal) {
            const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
            new G4LogicalBorderSurface{"couplerSurface",
                                       ecalCrystal->PhysicalVolume(fmt::format("ECALCrystal_{}", moduleID)),
                                       physicalCoupler,
                                       couplerSurface};
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"cathodeSkinSurface", logicCathode, cathodeSurface};
        cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);
        ++moduleID;
    }
}
} // namespace MACE::Detector::Definition
  // namespace MACE::Detector::Definition