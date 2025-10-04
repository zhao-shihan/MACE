#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

#include <unordered_set>

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;

auto PDSVeto::DefineMaterial() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto nistManager{G4NistManager::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};
    // SiPM material
    fSilicon = nistManager->FindOrBuildMaterial("G4_Si");
    // coupler material
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};
    fSiliconeGrease = new G4Material("vetoSiliconeGrease", 1.06_g_cm3, 4, kStateLiquid);
    fSiliconeGrease->AddElement(carbonElement, 2);
    fSiliconeGrease->AddElement(hydrogenElement, 6);
    fSiliconeGrease->AddElement(oxygenElement, 1);
    fSiliconeGrease->AddElement(siliconElement, 1);
    const auto siliconeGreasePropertiesTable{new G4MaterialPropertiesTable};
    siliconeGreasePropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.46, 1.46}); // EJ-550
    siliconeGreasePropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {100_cm, 100_cm});
    fSiliconeGrease->SetMaterialPropertiesTable(siliconeGreasePropertiesTable);
    // SiPM window material
    fEpoxy = new G4Material("epoxy", 1.18_g_cm3, 3, kStateSolid);
    fEpoxy->AddElement(carbonElement, 0.7362);
    fEpoxy->AddElement(hydrogenElement, 0.0675);
    fEpoxy->AddElement(oxygenElement, 0.1963);
    const auto epoxyPropertiesTable{new G4MaterialPropertiesTable};
    epoxyPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.59, 1.59}); // microft-30032-smt
    fEpoxy->SetMaterialPropertiesTable(epoxyPropertiesTable);
    // plastic scintillator material
    // fPlasticScintillaor = nistManager->FindOrBuidMaterial("G4_POLYSTYRENE");
    fPlasticScintillaor = new G4Material("Polyvinyl_toluene", 1.023_g_cm3, 2, kStateSolid);
    fPlasticScintillaor->AddElement(carbonElement, 9);
    fPlasticScintillaor->AddElement(hydrogenElement, 10);
    const auto plasticScintillatorPropertiesTable{new G4MaterialPropertiesTable};
    plasticScintillatorPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.58, 1.58});
    plasticScintillatorPropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {380_cm, 380_cm});
    plasticScintillatorPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", veto.PSScintillationEnergyBin(), veto.PSScintillationComponent1());
    plasticScintillatorPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", veto.PSScintillationYield());
    plasticScintillatorPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", veto.PSScintillationTimeConstant1());
    plasticScintillatorPropertiesTable->AddConstProperty("RESOLUTIONSCALE", veto.PSResolutionScale());
    fPlasticScintillaor->SetMaterialPropertiesTable(plasticScintillatorPropertiesTable);

    // air
    fAir = nistManager->FindOrBuildMaterial("G4_AIR");
    const auto airPropertiesTable{new G4MaterialPropertiesTable};
    airPropertiesTable->AddProperty("RINDEX", "Air");
    // airPropertiesTable->AddProperty("ABSLENGTH")
    fAir->SetMaterialPropertiesTable(airPropertiesTable);
    // Al
    fAl = nistManager->FindOrBuildMaterial("G4_Al");
    // fiber Outer - FP (Fluorinated polymer)
    // fFP = new G4Material("Fluorinated_Polymer", 1.43_g_cm3, 2, kStateSolid);
    // fFP->AddElement(carbonElement, 2);
    // fFP->AddElement(hydrogenElement, 4);
    // const auto fiberFPMaterial{new G4MaterialPropertiesTable};
    // fiberFPMaterial->AddProperty("RINDEX", veto.FPRIndexEnergy(), veto.FPRIndex());
    // fiberFPMaterial->AddProperty("ABSLENGTH", veto.FPAbsEnergy(), veto.FPAbsLength());
    // fFP->SetMaterialPropertiesTable(fiberFPMaterial);
    // fiber inner - PMMA
    fPMMA = new G4Material("PMMA", 1.19_g_cm3, 3, kStateSolid);
    fPMMA->AddElement(carbonElement, 5);
    fPMMA->AddElement(hydrogenElement, 8);
    fPMMA->AddElement(oxygenElement, 2);
    const auto fiberPMMAMaterial{new G4MaterialPropertiesTable};
    fiberPMMAMaterial->AddProperty("RINDEX", "PMMA");
    fiberPMMAMaterial->AddProperty("ABSLENGTH", veto.PMMAAbsEnergy(), veto.PMMAAbsLength());
    fPMMA->SetMaterialPropertiesTable(fiberPMMAMaterial);
    // fiber core - WLS PS
    fWlsPS = nistManager->BuildMaterialWithNewDensity("PDSVetoFiberCore", "G4_POLYSTYRENE", 1.05_g_cm3);
    // fWlsPS->SetFreeElectronDensity(1.19_g_cm3);
    // fWlsPS = new G4Material("Polystyrene", 1.05_g_cm3,2,kStateSolid);
    // fWlsPS->AddElement(carbonElement,1);
    // fWlsPS->AddElement(hydrogenElement,1);
    const auto WLSFiberMaterial{new G4MaterialPropertiesTable};
    WLSFiberMaterial->AddProperty("RINDEX", veto.WLSRIndexEnergy(), veto.WLSRIndex());
    WLSFiberMaterial->AddProperty("ABSLENGTH", veto.WLSVAbsEnergy(), veto.WLSVAbsLength());
    WLSFiberMaterial->AddProperty("WLSABSLENGTH", veto.WLSAbsEnergy(), veto.WLSAbsLength());
    WLSFiberMaterial->AddProperty("WLSCOMPONENT", veto.WLSEmissionEnergy(), veto.WLSEmissionAmplitude());
    WLSFiberMaterial->AddConstProperty("WLSTIMECONSTANT", 0.5_ns);
    fWlsPS->SetMaterialPropertiesTable(WLSFiberMaterial);
}

auto PDSVeto::ConstructLV() -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};
    // skin surface propertiestable set
    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0.985, 0.985});
    const auto transparentSurfacePropertiesTable{new G4MaterialPropertiesTable};
    transparentSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, {1., 1.});
    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", veto.SiPMEnergyBin(), veto.SiPMEfficiency());

    const auto& categoryConfiguration{veto.CategoryConfiguration()};
    for (int categoryID{}; categoryID < 4; ++categoryID) {
        const auto moduleLength{categoryConfiguration[categoryID].moduleLength};
        const auto moduleWidth{categoryConfiguration[categoryID].moduleWidth};
        const auto moduleThickness{categoryConfiguration[categoryID].moduleThickness};
        // define solids and logical volumes
        const auto solidModule{Make<G4Box>("VetoSolidModuleBox",
                                           moduleWidth / 2,
                                           moduleThickness / 2,
                                           moduleLength / 2)};
        const auto logicModule{Make<G4LogicalVolume>(solidModule, fAir, fmt::format("VetoModuleBox_{}", categoryID))};

        const auto solidStripBox{Make<G4Box>("VetoSolidStripBox",
                                             veto.PSWidth() / 2 + veto.ReflectiveFilmThickness(),
                                             veto.PSThickness() / 2 + veto.ReflectiveFilmThickness(),
                                             moduleLength / 2)};
        const auto logicStripBox{Make<G4LogicalVolume>(solidStripBox, fAir, fmt::format("VetoStripBox_{}", categoryID))};

        const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(logicStripBox->GetSolid())->GetZHalfLength()};
        const auto psStripLength{(stripBoxHalfLength - (veto.SiPMThickness() + veto.SiPMCouplerThickness())) * 2};
        const auto solidStrip{Make<G4Box>("VetoSolidStrip",
                                          veto.PSWidth() / 2,
                                          veto.PSThickness() / 2,
                                          psStripLength / 2)};
        const auto logicStrip{Make<G4LogicalVolume>(solidStrip, fPlasticScintillaor, fmt::format("VetoStrip_{}", categoryID))};
        // skin surface - strips
        const auto stripSurface{new G4OpticalSurface("Strip", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"VetoStripSkinSurface", logicStrip, stripSurface};
        stripSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto solidAlAbsorber{Make<G4Box>("VetoSolidAlAbsorber",
                                               dynamic_cast<const G4Box*>(logicModule->GetSolid())->GetXHalfLength(),
                                               veto.AlAbsorberThickness() / 2,
                                               psStripLength / 2)};
        Make<G4LogicalVolume>(solidAlAbsorber, fAl, fmt::format("VetoAlAbsorber_{}", categoryID));

        const auto fiberLength{psStripLength};
        const auto solidFiberHole{Make<G4Tubs>("VetoSolidFiberHole", 0., veto.FiberHoleRadius(), fiberLength / 2, 0., 2 * pi)};
        const auto logicFiberHole{Make<G4LogicalVolume>(solidFiberHole, fAir, fmt::format("VetoFiberHole_{}", categoryID))};
        const auto solidFiberOuter{Make<G4Tubs>("VetoSolidFiberOuter", 0., veto.FiberRadius(), fiberLength / 2, 0., 2 * pi)};
        const auto logicFiberOuter{Make<G4LogicalVolume>(solidFiberOuter, fPMMA, fmt::format("VetoFiberOuter_{}", categoryID))};
        const auto solidFiberInner{Make<G4Tubs>("VetoSolidFiberInner", 0., veto.FiberRadius() * veto.FiberInnerRadiusRatio(), fiberLength / 2, 0., 2 * pi)};
        const auto logicFiberInner{Make<G4LogicalVolume>(solidFiberInner, fPMMA, fmt::format("VetoFiberInner_{}", categoryID))};
        const auto solidFiberCore{Make<G4Tubs>("VetoSolidFiberCore", 0., veto.FiberRadius() * veto.FiberCoreRadiusRatio(), fiberLength / 2, 0., 2 * pi)};
        const auto logicFiberCore{Make<G4LogicalVolume>(solidFiberCore, fWlsPS, fmt::format("VetoFiberCore_{}", categoryID))};

        // skin surface - coupler, fiber, SiPMWindow
        const auto transparentSurface{new G4OpticalSurface("Fiber", unified, polished, dielectric_dielectric)};
        new G4LogicalSkinSurface{"VetoFiberHoleSkinSurface", logicFiberHole, transparentSurface};
        new G4LogicalSkinSurface{"VetoFiberOuterSkinSurface", logicFiberOuter, transparentSurface};
        new G4LogicalSkinSurface{"VetoFiberInnerSkinSurface", logicFiberInner, transparentSurface};
        new G4LogicalSkinSurface{"VetoFiberCoreSkinSurface", logicFiberCore, transparentSurface};
        transparentSurface->SetMaterialPropertiesTable(transparentSurfacePropertiesTable);
    }
    const auto solidSiPMCoupuler{Make<G4Box>("VetoSolidSiPMCoupler",
                                             veto.SiPMSize() / 2,
                                             veto.SiPMCouplerThickness() / 2,
                                             veto.SiPMSize() / 2)};
    const auto solidSiPM{Make<G4Box>("VetoSolidSiPM",
                                     veto.SiPMSize() / 2,
                                     veto.SiPMThickness() / 2,
                                     veto.SiPMSize() / 2)};
    const auto solidSiPMCathode{Make<G4Box>("VetoSolidSiPMCathode",
                                            veto.SiPMSize() / 2,
                                            veto.SiPMCathodeThickness() / 2,
                                            veto.SiPMSize() / 2)};
    Make<G4LogicalVolume>(solidSiPMCoupuler, fSiliconeGrease, "VetoSiPMCoupler");
    Make<G4LogicalVolume>(solidSiPM, fEpoxy, "VetoSiPM");
    const auto logicSiPM{Make<G4LogicalVolume>(solidSiPMCathode, fSilicon, "VetoCathode")};

    // surface cathode skin define
    const auto cathodeSurface{new G4OpticalSurface("VetoCathode", unified, polished, dielectric_metal)};
    new G4LogicalSkinSurface{"VetoCathodeSkinSurface", logicSiPM, cathodeSurface};
    cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

    // // temporary code for ecomug generator visualization
    // const auto solidGeneratorSphere{Make<G4Sphere>("VetoSolidGeneratorSphere",2_m,2.001_m,0.,1_pi,0.,2_pi)};
    // const auto logicGeneratorSphere{Make<G4LogicalVolume>(solidGeneratorSphere,fAir,"VetoGeneratorSphere")};
}

auto PDSVeto::Construct(bool checkOverlaps) -> void {
    const auto& veto{Description::PDSVeto::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(veto.PSScintillationEnergyBin())};
    DefineMaterial();
    ConstructLV();
    // surface definition
    // Make<G4PVPlacement>(G4Transform3D::Identity,
    //                     LogicalVolume("VetoGeneratorSphere"),
    //                     "VetoGeneratorSphere",
    //                     Mother().LogicalVolume(),
    //                     false,
    //                     0,
    //                     checkOverlaps);
    const auto airPaintSurfacePropertiesTable{new G4MaterialPropertiesTable};
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0, 0});
    // const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    // couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, {1, 1});
    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0.985, 0.985});
    const auto transparentSurfacePropertiesTable{new G4MaterialPropertiesTable};
    transparentSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, {1., 1.});

    if (veto.SelectedCategory() < -1 or veto.SelectedCategory() > 3) {
        Mustard::PrintWarning(fmt::format("\n no such category: category[{}]\n"
                                                   "available category selection:\n"
                                                   "category[-1] (All)\n",
                                                   "category[0] (Top)\n"
                                                   "category[1] (Side)\n"
                                                   "category[2] (Cap1)\n"
                                                   "category[3] (Cap2)\n"
                                                   veto.SelectedCategory()));
    }
    for (auto aCategoryConfiguration : veto.CategoryConfiguration()) {
        auto categoryID{aCategoryConfiguration.categoryID};
        auto singleStripTranslation{new G4ThreeVector()};
        auto singleModuleRotation{new G4Rotate3D()};
        if ((veto.SelectedCategory() != -1)) {
            if (categoryID != veto.SelectedCategory()) {
                continue;
            }
        }

        for (auto aModuleConfig : aCategoryConfiguration.modules) {
            auto phyModuleBox{Make<G4PVPlacement>(aModuleConfig.moduleTransform,
                                                  LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                                  fmt::format("VetoModuleBox_{}_{}", categoryID, aModuleConfig.moduleLocalID),
                                                  Mother().LogicalVolume(),
                                                  false,
                                                  aModuleConfig.moduleID,
                                                  checkOverlaps)};
            if (veto.SelectedCategory() != -1) {
                if (Mustard::Env::VerboseLevelReach<'V'>()) {
                    (*singleStripTranslation) += phyModuleBox->GetObjectTranslation();
                    (*singleModuleRotation) = phyModuleBox->GetObjectRotationValue();
                    fmt::println("@info\nSingle strip configuration info: ");
                    fmt::println("x_moduleBox: {},{},{}", phyModuleBox->GetObjectTranslation().getX(), phyModuleBox->GetObjectTranslation().getY(), phyModuleBox->GetObjectTranslation().getZ());
                }
                break;
            }
        }
        for (auto aLayerConfig : aCategoryConfiguration.modules[0].alLayers) {

            if (veto.SelectedCategory() == -1 and aLayerConfig.layerLocalID > 0) {
                Make<G4PVPlacement>(aLayerConfig.alAbsorberLocalTransform,
                                    LogicalVolume(fmt::format("VetoAlAbsorber_{}", categoryID)),
                                    fmt::format("VetoAlAbsorber_{}_allModules_{}", categoryID, aLayerConfig.layerLocalID),
                                    LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                    false,
                                    aLayerConfig.layerLocalID,
                                    checkOverlaps);
            }
        }
        for (auto aStripConfig : aCategoryConfiguration.modules[0].strips) {
            auto physicalStripBox{Make<G4PVPlacement>(aStripConfig.stripLocalTransform,
                                                      LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                                      fmt::format("VetoStripBox_{}", categoryID, aStripConfig.stripLocalID),
                                                      LogicalVolume(fmt::format("VetoModuleBox_{}", categoryID)),
                                                      false,
                                                      aStripConfig.stripLocalID,
                                                      checkOverlaps)};
            if (veto.SelectedCategory() != -1) {
                if (Mustard::Env::VerboseLevelReach<'V'>()) {
                    auto stripActualTranslation{*singleStripTranslation + physicalStripBox->GetObjectTranslation().transform(singleModuleRotation->getRotation())};
                    fmt::println("@info\nSingle strip configuration info: ");
                    fmt::println("x_stripBox: {},{},{}", stripActualTranslation.getX(), stripActualTranslation.getY(), stripActualTranslation.getZ());
                }
                break;
            }
        }
        // strips
        const auto physicalStrip{Make<G4PVPlacement>(G4Transform3D::Identity,
                                                     LogicalVolume(fmt::format("VetoStrip_{}", categoryID)),
                                                     fmt::format("VetoStrip_{}", categoryID),
                                                     LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                                     false,
                                                     0,
                                                     checkOverlaps)};

        // fibers
        const auto fiberNum{veto.FiberNum()};
        const auto fiberSpacing{veto.PSWidth() / (fiberNum)};
        for (int fiberCount{}; fiberCount < fiberNum; ++fiberCount) {
            const auto fiberCenterX{-veto.PSWidth() / 2 + fiberSpacing * (2 * fiberCount + 1) / 2};
            const G4Transform3D fiberTransform{
                G4RotationMatrix::IDENTITY, G4ThreeVector{fiberCenterX, 0, 0}
            };
            const auto physicalFiberHole{Make<G4PVPlacement>(fiberTransform,
                                                             LogicalVolume(fmt::format("VetoFiberHole_{}", categoryID)),
                                                             fmt::format("VetoFiberHole_{}", categoryID),
                                                             LogicalVolume(fmt::format("VetoStrip_{}", categoryID)),
                                                             false,
                                                             fiberCount,
                                                             checkOverlaps)};
            for (int sideCount{}; sideCount < 2; ++sideCount) {                              // loop by one pairs' 2 sides
                const auto readBoxRotation{G4RotateX3D{std::pow(-1., sideCount) * pi / 2.}}; // SiPM&coupler
                const auto stripBoxHalfLength{dynamic_cast<const G4Box*>(LogicalVolume(fmt::format("VetoStripBox_{}", categoryID))->GetSolid())->GetZHalfLength()};
                const auto SiPMPosZ{(stripBoxHalfLength - veto.SiPMThickness() / 2)};
                const auto couplerPosZ{stripBoxHalfLength - veto.SiPMThickness() - veto.SiPMCouplerThickness() / 2};
                G4Transform3D couplerTransform{
                    readBoxRotation.getRotation(), G4ThreeVector{fiberCenterX, 0, couplerPosZ * std::pow(-1., sideCount)}
                };
                G4Transform3D SiPMTransform{
                    readBoxRotation.getRotation(), G4ThreeVector{fiberCenterX, 0, SiPMPosZ * std::pow(-1., sideCount)}
                };

                auto physicalCoupler{Make<G4PVPlacement>(couplerTransform,
                                                         LogicalVolume("VetoSiPMCoupler"),
                                                         "VetoSiPMCoupler",
                                                         LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                                         false,
                                                         sideCount,
                                                         checkOverlaps)};
                // border surface fiberHole -> coupler
                const auto fiberHoleToCoupler{new G4OpticalSurface("borderSurface_fiberHole_to_coupler", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"VetoBorderSurface_fiberHole_to_coupler",
                                           physicalFiberHole,
                                           physicalCoupler,
                                           fiberHoleToCoupler};
                fiberHoleToCoupler->SetMaterialPropertiesTable(transparentSurfacePropertiesTable);

                Make<G4PVPlacement>(SiPMTransform,
                                    LogicalVolume("VetoSiPM"),
                                    "VetoSiPM",
                                    LogicalVolume(fmt::format("VetoStripBox_{}", categoryID)),
                                    false,
                                    fiberCount * 2 + sideCount,
                                    checkOverlaps);
            }
        }
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoFiberOuter_{}", categoryID)),
                            fmt::format("VetoFiberOuter_{}", categoryID),
                            LogicalVolume(fmt::format("VetoFiberHole_{}", categoryID)),
                            false,
                            0,
                            checkOverlaps);
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoFiberInner_{}", categoryID)),
                            fmt::format("VetoFiberInner_{}", categoryID),
                            LogicalVolume(fmt::format("VetoFiberOuter_{}", categoryID)),
                            false,
                            0,
                            checkOverlaps);
        Make<G4PVPlacement>(G4Transform3D::Identity,
                            LogicalVolume(fmt::format("VetoFiberCore_{}", categoryID)),
                            fmt::format("VetoFiberCore_{}", categoryID),
                            LogicalVolume(fmt::format("VetoFiberInner_{}", categoryID)),
                            false,
                            0,
                            checkOverlaps);

        // border surface air -> strips
        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        for (auto physicalStripBox : PhysicalVolumes(fmt::format("VetoStripBox_{}", categoryID))) {
            new G4LogicalBorderSurface{"VetoAirPaintSurface", physicalStripBox, physicalStrip, airPaintSurface};
        }
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);

        // border surface strip -> coupler
        for (auto physicalCoupler : PhysicalVolumes("VetoSiPMCoupler")) {
            if (physicalStrip && physicalCoupler) {
                const auto stripToCoupler{new G4OpticalSurface("borderSurface_strip_to_coupler", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"VetoBorderSurface_strip_to_coupler",
                                           physicalStrip,
                                           physicalCoupler,
                                           stripToCoupler};
                stripToCoupler->SetMaterialPropertiesTable(transparentSurfacePropertiesTable);
            }
        }
        // border surface fiber -> coupler
        const auto fiberToCoupler{new G4OpticalSurface("VetoBorderSurface_fiber_to_coupler", unified, polished, dielectric_dielectric)};
        for (auto physicalCoupler : PhysicalVolumes("VetoSiPMCoupler")) {
            for (auto physicalFiberOuter : PhysicalVolumes(fmt::format("VetoFiberOuter_{}", categoryID))) {
                if (physicalFiberOuter) {
                    new G4LogicalBorderSurface{"VetoBorderSurface_fiberOuter_to_coupler",
                                               physicalFiberOuter,
                                               physicalCoupler,
                                               fiberToCoupler};
                }
            }
            for (auto physicalFiberInner : PhysicalVolumes(fmt::format("VetoFiberInner_{}", categoryID))) {
                if (physicalFiberInner) {
                    new G4LogicalBorderSurface{"VetoBorderSurface_fiberInner_to_coupler",
                                               physicalFiberInner,
                                               physicalCoupler,
                                               fiberToCoupler};
                }
            }
            for (auto physicalFiberCore : PhysicalVolumes(fmt::format("VetoFiberCore_{}", categoryID))) {
                if (physicalFiberCore) {
                    new G4LogicalBorderSurface{"VetoBorderSurface_fiberCore_to_coupler",
                                               physicalFiberCore,
                                               physicalCoupler,
                                               fiberToCoupler};
                }
            }
        }
        fiberToCoupler->SetMaterialPropertiesTable(transparentSurfacePropertiesTable);

        // border surface strips -> fiberholes
        for (auto physicalFiberHole : PhysicalVolumes(fmt::format("VetoFiberHole_{}", categoryID))) {
            if (physicalStrip && physicalFiberHole) {
                const auto stripToFiberHole{new G4OpticalSurface("borderSurface_strip_to_fiberHole", unified, polished, dielectric_dielectric)};
                new G4LogicalBorderSurface{"VetoBorderSurface_strip_to_fiberHole",
                                           physicalStrip,
                                           physicalFiberHole,
                                           stripToFiberHole};
            }
        }
    }
    const auto cathodeRelativePosY{veto.SiPMThickness() / 2 - veto.SiPMCathodeThickness() / 2};
    G4Transform3D cathodeRelativeTransform{
        G4RotationMatrix::IDENTITY, G4ThreeVector{0, cathodeRelativePosY, 0}
    };
    Make<G4PVPlacement>(cathodeRelativeTransform,
                        LogicalVolume("VetoCathode"),
                        "VetoCathode",
                        LogicalVolume("VetoSiPM"),
                        false,
                        0,
                        checkOverlaps);
}
} // namespace MACE::Detector::Definition
