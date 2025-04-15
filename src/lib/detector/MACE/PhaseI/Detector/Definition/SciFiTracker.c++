#include "MACE/PhaseI/Detector/Definition/SciFiTracker.h++"
#include "MACE/PhaseI/Detector/Description/SciFiTracker.h++"

#include "Mustard/Extension/Geant4X/Geometry/HelicalBox.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <utility>

namespace MACE::PhaseI::Detector::Definition {

using namespace Mustard::PhysicalConstant;
using namespace Mustard::MathConstant;
using namespace Mustard::LiteralUnit;

auto SciFiTracker::Construct(G4bool checkOverlaps) -> void {
    const auto& sciFiTracker{Description::SciFiTracker::Instance()};
    const auto name{sciFiTracker.Name()};
    const auto nistManager{G4NistManager::Instance()};

    const auto silicon{nistManager->FindOrBuildMaterial("G4_Si")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};
    const auto fluorineElement{nistManager->FindOrBuildElement("F")};
    const auto chlorineElement{nistManager->FindOrBuildElement("Cl")};

    const auto siliconeOil{new G4Material("silicone_oil", 0.97_g_cm3, 4, kStateLiquid)};
    siliconeOil->AddElement(carbonElement, 2);
    siliconeOil->AddElement(hydrogenElement, 6);
    siliconeOil->AddElement(oxygenElement, 1);
    siliconeOil->AddElement(siliconElement, 1);

    const auto fp = new G4Material("FP", 1.43_g_cm3, 4, kStateSolid);
    fp->AddElement(carbonElement, 2);
    fp->AddElement(hydrogenElement, 2);
    fp->AddElement(chlorineElement, 1);
    fp->AddElement(fluorineElement, 5);

    const auto pmma = new G4Material("PMMA", 1.19_g_cm3, 3, kStateSolid);
    pmma->AddElement(carbonElement, 5);
    pmma->AddElement(hydrogenElement, 8);
    pmma->AddElement(oxygenElement, 2);

    const auto ps = new G4Material("PS", 1.05_g_cm3, 2, kStateSolid);
    ps->AddElement(carbonElement, 1);
    ps->AddElement(hydrogenElement, 1);
    ps->GetIonisation()->SetBirksConstant(0.126); // https://geant4-forum.web.cern.ch/t/birks-constant-for-different-materials/1014/3

    const auto epoxy{new G4Material("Epoxy", 1.18_g_cm3, 3, kStateSolid)};
    epoxy->AddElement(carbonElement, 0.7362);
    epoxy->AddElement(hydrogenElement, 0.0675);
    epoxy->AddElement(oxygenElement, 0.1963);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambda_min = 200_nm;
    constexpr auto fLambda_max = 700_nm;
    std::vector<G4double> fEnergyPair{h_Planck * c_light / fLambda_max,
                                      h_Planck * c_light / fLambda_min};

    std::vector<G4double> scintillationEnergyBin(sciFiTracker.ScintillationWaveLengthBin().size());
    std::ranges::transform(sciFiTracker.ScintillationWaveLengthBin(),
                           scintillationEnergyBin.begin(),
                           [](auto val) { return h_Planck * c_light / (val * 1_nm); });
    std::vector<G4double> scintillationComponent(sciFiTracker.ScintillationComponent1().size());
    for (int i{}; i < std::ssize(sciFiTracker.ScintillationComponent1()); i++) {
        scintillationComponent[i] = sciFiTracker.ScintillationComponent1()[i] * h_Planck * c_light / scintillationEnergyBin[i] / scintillationEnergyBin[i];
    }

    //============================================ Optical Window =====================================

    const auto windowPropertiesTable = new G4MaterialPropertiesTable();
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.55, 1.55});
    epoxy->SetMaterialPropertiesTable(windowPropertiesTable);

    const auto siliconeOilPropertiesTable{new G4MaterialPropertiesTable()};
    siliconeOilPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.465, 1.465});
    siliconeOilPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {40_cm, 40_cm});
    siliconeOil->SetMaterialPropertiesTable(siliconeOilPropertiesTable);

    const auto epoxyPropertiesTable{new G4MaterialPropertiesTable()};
    epoxyPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.55, 1.55});
    epoxy->SetMaterialPropertiesTable(epoxyPropertiesTable);

    const auto plasticPropertiesTable = new G4MaterialPropertiesTable();
    plasticPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.59, 1.59});
    plasticPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {4_m, 4_m});
    plasticPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", scintillationEnergyBin, scintillationComponent);
    plasticPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 8000);
    plasticPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", sciFiTracker.ScintillationTimeConstant1());
    plasticPropertiesTable->AddConstProperty("RESOLUTIONSCALE", 1.0);
    ps->SetMaterialPropertiesTable(plasticPropertiesTable);

    const auto pmmaPropertiesTable{new G4MaterialPropertiesTable()};
    pmmaPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.49, 1.49});
    pmmaPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {4_m, 4_m});
    pmma->SetMaterialPropertiesTable(pmmaPropertiesTable);

    const auto fpPropertiesTable{new G4MaterialPropertiesTable()};
    fpPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.363, 1.363});
    fpPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {4_m, 4_m});
    fp->SetMaterialPropertiesTable(fpPropertiesTable);

    //============================================ Surface ============================================

    const auto sipmSurfacePropertiesTable{new G4MaterialPropertiesTable()};
    sipmSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    sipmSurfacePropertiesTable->AddProperty("EFFICIENCY", sciFiTracker.SiPMEnergyBin(), sciFiTracker.SiPMQuantumEfficiency());

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0, 0});

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    /////////////////////////////////////////
    ///////////solid and logical/////////////
    /////////////////////////////////////////
    for (int i{}; i < sciFiTracker.NLayer(); i += 2) {
        const auto solidBracket1{Make<G4Tubs>("Bracket",
                                              sciFiTracker.RLayer()->at(i) - sciFiTracker.FiberCladdingWidth() - 2,
                                              sciFiTracker.RLayer()->at(i) - sciFiTracker.FiberCladdingWidth(),
                                              sciFiTracker.FiberLength() / 2, 0,
                                              2_pi)};
        const auto logicalBracket1{
            Make<G4LogicalVolume>(solidBracket1,
                                  G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"),
                                  "Bracket")};
        Make<G4PVPlacement>(nullptr,
                            G4ThreeVector(),
                            logicalBracket1,
                            "Bracket",
                            Mother().LogicalVolume(),
                            false,
                            0,
                            checkOverlaps);
    }

    const auto solidSiPM{
        Make<G4Box>("SciFiSiPM", sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.SiPMWidth() / 2,
                    (sciFiTracker.SiPMThickness() + sciFiTracker.SiliconeOilThickness() + sciFiTracker.EpoxyThickness()) / 2)};
    const auto logicalSiPM{Make<G4LogicalVolume>(solidSiPM, silicon, "SciFiSiPM")};

    const auto solidEpoxy{
        Make<G4Box>("SciFiEpoxy",
                    sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.EpoxyThickness() / 2)};
    const auto logicalEpoxy{Make<G4LogicalVolume>(solidEpoxy, epoxy, "SciFiEpoxy")};

    const auto solidSiliconeOil{
        Make<G4Box>("SciFiSiliconeOil",
                    sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.SiliconeOilThickness() / 2)};
    const auto logicalSiliconeOil{Make<G4LogicalVolume>(solidSiliconeOil, siliconeOil, "SciFiSiliconeOil")};

    const auto solidAbsorbLayer{
        Make<G4Box>("SciFiAbsorbLayer",
                    sciFiTracker.SiPMLength() / 2,
                    sciFiTracker.SiPMLength() / 2,
                    (sciFiTracker.SiPMThickness() + sciFiTracker.SiliconeOilThickness() + sciFiTracker.EpoxyThickness()) / 2)};
    const auto logicalAbsorbLayer{Make<G4LogicalVolume>(solidAbsorbLayer, silicon, "SciFiAbsorbLayer")};

    Make<G4PVPlacement>(
        nullptr, G4ThreeVector(0, 0, (sciFiTracker.SiliconeOilThickness() - sciFiTracker.SiPMThickness()) / 2),
        logicalEpoxy,
        "SciFiEpoxy",
        logicalSiPM,
        false,
        0,
        checkOverlaps);

    Make<G4PVPlacement>(
        nullptr, G4ThreeVector(0, 0, -(sciFiTracker.EpoxyThickness() + sciFiTracker.SiPMThickness()) / 2),
        logicalSiliconeOil,
        "SciFiSiliconeOil",
        logicalSiPM,
        false,
        0,
        checkOverlaps);

    auto rotationVector{
        [&](double i, double pitch, double x0, double y0, double pm_z) {
            return CLHEP::Hep3Vector(
                std::cos(i) * x0 - std::sin(i) * y0,
                std::cos(i) * y0 + std::sin(i) * x0,
                pm_z * ((sciFiTracker.SiPMThickness() + sciFiTracker.SiliconeOilThickness() + sciFiTracker.EpoxyThickness()) / 2 +
                        sciFiTracker.FiberLength() / 2 + sciFiTracker.LightGuideCurvature() * std::cos(pitch)));
        }};

    auto logicalFiber{
        [&](auto helicalradius, auto fibercladdingwidth, auto fibercorewidth, auto pitch, std::string name) {
            const auto solidcladding{Make<Mustard::Extension::Geant4X::HelicalBox>(
                name + "Fiber",
                helicalradius,
                fibercladdingwidth,
                pitch,
                0,
                2_pi,
                0.001)};
            const auto logicalcladding{Make<G4LogicalVolume>(
                solidcladding,
                pmma,
                name + "Fiber")};
            const auto solidcore{Make<Mustard::Extension::Geant4X::HelicalBox>(
                "SciFiCore",
                helicalradius,
                fibercorewidth,
                pitch,
                0,
                2_pi,
                0.001)};
            const auto logicalcore{Make<G4LogicalVolume>(solidcore, ps, "SciFiCore")};

            Make<G4PVPlacement>(G4Transform3D{},
                                logicalcore, "SciFiCore", logicalcladding, false, 0, checkOverlaps);
            return logicalcladding;
        }};

    auto logicalLightGuide{
        [&](auto curvature, auto fibercladdingwidth, auto fibercorewidth, auto pitch, std::string name) {
            const auto solidcladding{Make<G4Tubs>(
                name + "SciFiLightGuide",
                curvature - fibercladdingwidth / 2,
                curvature + fibercladdingwidth / 2,
                fibercladdingwidth / 2,
                0,
                0.5_pi - std::abs(pitch))};

            const auto solidcore{Make<G4Tubs>(
                name + "SciFiLightGuide",
                curvature - fibercorewidth / 2,
                curvature + fibercorewidth / 2,
                fibercorewidth / 2,
                0,
                0.5_pi - std::abs(pitch))};

            const auto logicalcladding{Make<G4LogicalVolume>(
                solidcladding,
                fp,
                name + "SciFiLightGuide")};

            const auto logicalcore{Make<G4LogicalVolume>(
                solidcore,
                pmma,
                name + "SciFiLightGuide")};

            Make<G4PVPlacement>(G4Transform3D{},
                                logicalcore, name + "SciFiLightGuide", logicalcladding, false, 0, checkOverlaps);

            return logicalcladding;
        }};

    auto logicalTransverseFiber{[&](auto fiberCladdingWidth, auto fiberCoreWidth, auto fiberLength, std::string name) {
        const auto solidTFiber{Make<G4Box>(
            name,
            fiberCladdingWidth / 2,
            fiberCladdingWidth / 2,
            fiberLength / 2)};

        const auto logicalTFiber{Make<G4LogicalVolume>(
            solidTFiber,
            pmma,
            "TransverseFiber")};
        const auto solidTransverseCore{Make<G4Box>(
            "SciFiCore",
            fiberCoreWidth / 2,
            fiberCoreWidth / 2,
            fiberLength / 2)};

        const auto logicalTransversecore{Make<G4LogicalVolume>(solidTransverseCore, ps, "SciFiCore")};
        Make<G4PVPlacement>(G4Transform3D{},
                            logicalTransversecore, "SciFiCore", logicalTFiber, false, 0, checkOverlaps);

        return logicalTFiber;
    }};

    auto logicalTransverseLightGuide{[&](auto fiberCladdingWidth, auto fiberCoreWidth, auto lightGuideLength, std::string name) {
        const auto solidTLightGuideCladding{Make<G4Box>(
            name + "SciFiLightGuide",
            fiberCladdingWidth / 2,
            fiberCladdingWidth / 2,
            lightGuideLength / 2)};

        const auto solidTLightGuideCore{Make<G4Box>(
            name + "SciFiLightGuide",
            fiberCoreWidth / 2,
            fiberCoreWidth / 2,
            lightGuideLength / 2)};

        const auto logicalTLightGuide{Make<G4LogicalVolume>(solidTLightGuideCladding, fp, name + "SciFiLightGuide")};
        const auto logicalTLightGuideCore{Make<G4LogicalVolume>(solidTLightGuideCore, pmma, name + "SciFiLightGuide")};
        Make<G4PVPlacement>(G4Transform3D{},
                            logicalTLightGuideCore, name + "SciFiLightGuide", logicalTLightGuide, false, 0, checkOverlaps);

        return logicalTLightGuide;
    }};

    /////////////////////////////////
    ///////////placement/////////////
    /////////////////////////////////
    int fiberNumber{};
    int sipmNumber{};
    auto HelicalPlacement{
        [&](auto helicalradius, auto logicalfiber, auto logicallightguide, auto NofFiber, auto pitch, auto curvature, std::string name, int second) {
            for (int i{}; i < NofFiber; i++) {
                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber},
                    logicalfiber,
                    name + "Fiber",
                    Mother().LogicalVolume(),
                    false,
                    fiberNumber++,
                    checkOverlaps);
                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4RotateY3D{0.5_pi} *
                        G4Translate3D{-sciFiTracker.FiberLength() / 2, 0, std::copysign(helicalradius, pitch)} *
                        G4RotateZ3D{std::abs(pitch)} *
                        G4TranslateX3D{-curvature},
                    logicallightguide,
                    name + "SciFiLightGuide",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4RotateY3D{0.5_pi} *
                        G4Translate3D{sciFiTracker.FiberLength() / 2, 0, std::copysign(helicalradius, pitch)} *
                        G4RotateZ3D{std::abs(pitch) + 1_pi} *
                        G4TranslateX3D{-curvature},
                    logicallightguide,
                    name + "SciFiLightGuide",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4Transform3D{
                        CLHEP::HepRotationZ{(i + second * 0.5) * 2_pi / NofFiber},
                        rotationVector((i + second * 0.5) * 2_pi / NofFiber,
                                       pitch,
                                       std::copysign(helicalradius, pitch),
                                       curvature * (1 - std::abs(std::sin(pitch))), 1)},
                    logicalSiPM,
                    name + "SciFiSiPM",
                    Mother().LogicalVolume(),
                    false,
                    sipmNumber++,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4Transform3D{
                        CLHEP::HepRotationZ{(i + second * 0.5) * 2_pi / NofFiber},
                        rotationVector((i + second * 0.5) * 2_pi / NofFiber,
                                       pitch,
                                       -std::copysign(helicalradius, pitch),
                                       curvature * (1 - std::abs(std::sin(pitch))), -1)},
                    logicalAbsorbLayer,
                    name + "SciFiAbsorbLayer",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);
            }
        }};

    auto TransversePlacement{
        [&](auto radius, auto logicalfiber, auto logicallightguide, auto NofFiber, std::string name, int second) {
            for (int i{}; i < NofFiber; i++) {
                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4Transform3D{
                            {},
                            G4ThreeVector(radius, 0, 0)},
                    logicalfiber,
                    name + "Fiber",
                    Mother().LogicalVolume(),
                    false,
                    fiberNumber++,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4Transform3D{
                            {},
                            G4ThreeVector(radius, 0, sciFiTracker.FiberLength() / 2 + sciFiTracker.TLightGuideLength() / 2)},
                    logicallightguide,
                    name + "SciFiLightGuide",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4Transform3D{
                            {},
                            G4ThreeVector(radius, 0, -(sciFiTracker.FiberLength() / 2 + sciFiTracker.TLightGuideLength() / 2))},
                    logicallightguide,
                    name + "SciFiLightGuide",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4Transform3D{
                            {},
                            G4ThreeVector(radius,
                                          0,
                                          (sciFiTracker.SiPMThickness() + sciFiTracker.SiliconeOilThickness() + sciFiTracker.EpoxyThickness() +
                                           sciFiTracker.FiberLength()) /
                                                  2 +
                                              sciFiTracker.TLightGuideLength())},
                    logicalSiPM,
                    name + "SciFiSiPM",
                    Mother().LogicalVolume(),
                    false,
                    sipmNumber++,
                    checkOverlaps);

                Make<G4PVPlacement>(
                    G4RotateZ3D{(i + second * 0.5) * 2_pi / NofFiber} *
                        G4Transform3D{
                            {},
                            G4ThreeVector(radius,
                                          0,
                                          -(sciFiTracker.SiPMThickness() + sciFiTracker.SiliconeOilThickness() + sciFiTracker.EpoxyThickness() +
                                            sciFiTracker.FiberLength()) /
                                                  2 -
                                              sciFiTracker.TLightGuideLength())},
                    logicalAbsorbLayer,
                    name + "SciFiAbsorbLayer",
                    Mother().LogicalVolume(),
                    false,
                    0,
                    checkOverlaps);
            }
        }};

    const auto layerConfig{sciFiTracker.DetectorLayerConfiguration()};
    for (int i{}; i < sciFiTracker.NLayer(); i++) {
        if (layerConfig[i].fiber.layerType == "LHelical") {
            auto logicalLFiber{logicalFiber(
                layerConfig[i].fiber.radius,
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                layerConfig[i].fiber.pitch,
                layerConfig[i].name)};

            auto logicalLLightGuide{logicalLightGuide(
                sciFiTracker.LightGuideCurvature(),
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                layerConfig[i].fiber.pitch,
                layerConfig[i].name)};

            HelicalPlacement(layerConfig[i].fiber.radius,
                             logicalLFiber,
                             logicalLLightGuide,
                             layerConfig[i].lastID - layerConfig[i].firstID + 1, // number of fiber is (end-begin+1)
                             layerConfig[i].fiber.pitch,
                             sciFiTracker.LightGuideCurvature(),
                             layerConfig[i].name, layerConfig[i].isSecond);
        } else if (layerConfig[i].fiber.layerType == "RHelical") {
            auto logicalRFiber{logicalFiber(
                layerConfig[i].fiber.radius,
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                layerConfig[i].fiber.pitch,
                layerConfig[i].name)};

            auto logicalRLightGuide{logicalLightGuide(
                sciFiTracker.LightGuideCurvature(),
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                layerConfig[i].fiber.pitch,
                layerConfig[i].name)};

            HelicalPlacement(layerConfig[i].fiber.radius,
                             logicalRFiber,
                             logicalRLightGuide,
                             layerConfig[i].lastID - layerConfig[i].firstID + 1, // number of fiber is (end-begin+1)
                             layerConfig[i].fiber.pitch,
                             sciFiTracker.LightGuideCurvature(),
                             layerConfig[i].name, layerConfig[i].isSecond);
        } else if (layerConfig[i].fiber.layerType == "Transverse") {
            auto logicalTFiber{logicalTransverseFiber(
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                sciFiTracker.FiberLength(),
                layerConfig[i].name)};

            auto logicalTLightGuide{logicalTransverseLightGuide(
                sciFiTracker.FiberCladdingWidth(),
                sciFiTracker.FiberCoreWidth(),
                sciFiTracker.TLightGuideLength(),
                layerConfig[i].name)};

            TransversePlacement(layerConfig[i].fiber.radius,
                                logicalTFiber,
                                logicalTLightGuide,
                                layerConfig[i].lastID - layerConfig[i].firstID + 1, // number of fiber is (end-begin+1)
                                layerConfig[i].name,
                                layerConfig[i].isSecond);
        }
    }

    /////////////////////////////////////////////
    // Construct Optical Surface
    /////////////////////////////////////////////

    const auto sipmSurface{new G4OpticalSurface("SiPMSurface", unified, polished, dielectric_metal)};
    sipmSurface->SetMaterialPropertiesTable(sipmSurfacePropertiesTable);
    new G4LogicalSkinSurface{"SiPMSurface", logicalSiPM, sipmSurface};

    const auto rfSurface{new G4OpticalSurface("rfSurface", unified, polished, dielectric_metal)};
    rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);
    new G4LogicalSkinSurface{"AbsorbSurface", logicalAbsorbLayer, rfSurface};
}

} // namespace MACE::PhaseI::Detector::Definition
