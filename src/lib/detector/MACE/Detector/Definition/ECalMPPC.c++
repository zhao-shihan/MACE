#include "MACE/Detector/Definition/ECalCrystal.h++"
#include "MACE/Detector/Definition/ECalMPPC.h++"
#include "MACE/Detector/Description/ECal.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

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

auto ECalPhotoSensor::Construct(G4bool checkOverlaps) -> void {
    if (Detector::Description::ECal::Instance().UseMPPC()) {
        ConstructMPPC(checkOverlaps);
    } else {
        ConstructPMT(checkOverlaps);
    }
}

auto ECalPhotoSensor::ConstructMPPC(G4bool checkOverlaps) -> void {

    class MPPCParameterisation : public G4VPVParameterisation {
    public:
        MPPCParameterisation(G4int NPixelRows, G4double PixelSize, G4double Pitch, G4double windowThickness, G4double mppcThickness);

        virtual ~MPPCParameterisation() = default;

        auto ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const -> void override {
            int rowNum{copyNo / fNPixelRows};
            int colNum{copyNo % fNPixelRows};
            // row&col start from 0
            double xOffSet{(2 * rowNum + 1 - fNPixelRows) * ((fPixelSize + fPitch) / 2)};
            double yOffset{(2 * colNum + 1 - fNPixelRows) * ((fPixelSize + fPitch) / 2)};
            double zOffset{(fwindowThickness - fmppcThickness) / 2};
            physVol->SetTranslation({xOffSet, yOffset, zOffset});
        }

        auto ComputeDimensions(G4Box& SiPixel, const G4int copyNo, const G4VPhysicalVolume* physVol) const -> void override {
            SiPixel.SetXHalfLength(fPixelSize / 2);
            SiPixel.SetYHalfLength(fPixelSize / 2);
            SiPixel.SetZHalfLength(fmppcThickness / 2);
        }

    private:
        G4int fNPixelRows;
        G4double fPixelSize;
        G4double fPitch;
        G4double fwindowThickness;
        G4double fmppcThickness;
    };

    const auto& eCal{Description::ECal::Instance()};
    const auto name{eCal.Name()};
    const auto& faceList{eCal.Mesh().fFaceList};
    const auto& typeMap{eCal.Mesh().fTypeMap};

    const auto mppcNPixelRows{eCal.MPPCNPixelRows()};
    const auto mppcPixelSizeSet{eCal.MPPCPixelSizeSet()};
    const auto mppcPitch{eCal.MPPCPitch()};
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
        int mppcNPixelRow{mppcNPixelRows.at(typeMapIt->second)};
        double mppcPixelSize{mppcPixelSizeSet.at(typeMapIt->second)};
        const auto mppcWidth{mppcNPixelRow * (mppcPixelSize + mppcPitch) + mppcPitch};
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

        // change volume window from epoxy to epoxy&silicon Pixels, may change name "window" later
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
        const auto mppcParam{new MPPCParameterisation(mppcNPixelRow, mppcPixelSize, mppcPitch, mppcWindowThickness, mppcThickness)};
        Make<G4PVParameterised>("SiPixels",
                                logicMPPC,
                                logicWindow,
                                kUndefined,
                                mppcNPixelRow,
                                mppcParam,
                                checkOverlaps);

        // Make<G4PVPlacement>(cathodeTransform,
        //                     logicMPPC,
        //                     "ECalMPPC",
        //                     Mother().LogicalVolume(),
        //                     true,
        //                     moduleID,
        //                     checkOverlaps);

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
};
auto ECalPhotoSensor::ConstructPMT(G4bool checkOverlaps) -> void {
    const auto& eCal{Description::ECal::Instance()};

    const auto pmtCouplerThickness{eCal.PMTCouplerThickness()};
    const auto pmtWindowThickness{eCal.PMTWindowThickness()};
    const auto pmtCathodeThickness{eCal.PMTCathodeThickness()};

    const auto pmtWaveLengthBin{eCal.PMTWaveLengthBin()};
    const auto pmtQuantumEfficiency{eCal.PMTQuantumEfficiency()};

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

    const auto& faceList{eCal.Mesh().fFaceList};
    const auto& typeMap{eCal.Mesh().fTypeMap};
    const auto& pmtDimensions{eCal.PMTDimensions()};

    for (int moduleID{};
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all ECal face

        // if(moduleID != 213){
        //     moduleID++;
        //     continue;
        // }

        auto typeMapIt = typeMap.find(moduleID);
        auto pmtDiameter = pmtDimensions.at(typeMapIt->second).at(0);
        auto cathodeDiameter = pmtDimensions.at(typeMapIt->second).at(1);
        auto pmtLength = pmtDimensions.at(typeMapIt->second).at(2);

        const auto couplerTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  pmtCouplerThickness / 2)};

        const auto shellTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                pmtCouplerThickness + pmtLength / 2)};

        const auto cathodeTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2)};

        const auto solidCoupler{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtCouplerThickness / 2, 0, 2 * pi)};
        const auto logicCoupler{Make<G4LogicalVolume>(solidCoupler, siliconeGrease, "ECalPMTCoupler")};
        const auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                       logicCoupler,
                                                       "ECalPMTCoupler",
                                                       Mother().LogicalVolume(),
                                                       true,
                                                       moduleID,
                                                       checkOverlaps)};

        const auto solidGlassTube{Make<G4Tubs>("temp", 0, pmtDiameter / 2, pmtLength / 2, 0, 2 * pi)};
        const auto solidPMTVacuum{Make<G4Tubs>("temp", 0, pmtDiameter / 2 - pmtWindowThickness, pmtLength / 2 - pmtWindowThickness, 0, 2 * pi)};
        const auto solidPMTShell{Make<G4SubtractionSolid>("ECalPMTShell", solidGlassTube, solidPMTVacuum)};
        const auto logicPMTShell{Make<G4LogicalVolume>(solidPMTShell, glass, "ECalPMTShell")};
        Make<G4PVPlacement>(shellTransform,
                            logicPMTShell,
                            "ECalPMTShell",
                            Mother().LogicalVolume(),
                            true,
                            moduleID,
                            checkOverlaps);

        const auto solidCathode{Make<G4Tubs>("temp", 0, cathodeDiameter / 2, pmtCathodeThickness / 2, 0, 2 * pi)};
        const auto logicCathode{Make<G4LogicalVolume>(solidCathode, bialkali, "ECalPMTCathode")};
        Make<G4PVPlacement>(cathodeTransform,
                            logicCathode,
                            "ECalPMTCathode",
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

        const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"cathodeSkinSurface", logicCathode, cathodeSurface};
        cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        ++moduleID;
    }
}
} // namespace MACE::Detector::Definition
  // namespace MACE::Detector::Definition