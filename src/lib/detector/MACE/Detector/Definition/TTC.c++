#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Description/TTC.h++"

#include "Mustard/Math/Parity.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include "gsl/gsl"

#include "fmt/format.h"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto TTC::Construct(G4bool checkOverlaps) -> void {
    const auto& ttc{Description::TTC::Instance()};
    const auto nistManager{G4NistManager::Instance()};
    // Define Element and Material
    const auto& ttcScintillatorMaterial{nistManager->BuildMaterialWithNewDensity("TTCScintillatorMaterial", "G4_POLYSTYRENE", ttc.Density())};

    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};

    const auto lightCoupler{new G4Material("TTCLightCouplerMaterial", ttc.LightCouplerDensity(), 4, kStateLiquid)};
    lightCoupler->AddElement(carbonElement, ttc.LightCouplerCarbonElement());
    lightCoupler->AddElement(hydrogenElement, ttc.LightCouplerHydrogenElement());
    lightCoupler->AddElement(oxygenElement, ttc.LightCouplerOxygenElement());
    lightCoupler->AddElement(siliconElement, ttc.LightCouplerSiliconElement());

    const auto window{new G4Material("TTCWindowMaterial", ttc.WindowDensity(), 3, kStateSolid)};
    window->AddElement(carbonElement, ttc.WindowCarbonElement());
    window->AddElement(hydrogenElement, ttc.WindowHydrogenElement());
    window->AddElement(oxygenElement, ttc.WindowOxygenElement());

    // Construct Material Optical Properties Tables
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(ttc.ScintillationComponent1EnergyBin())};
    const auto scintillatorPropertiesTable{new G4MaterialPropertiesTable};
    scintillatorPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, ttc.RIndex());
    scintillatorPropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, ttc.AbsLength());
    scintillatorPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", ttc.ScintillationComponent1EnergyBin(), ttc.ScintillationComponent1());
    scintillatorPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", ttc.ScintillationYield());
    scintillatorPropertiesTable->AddConstProperty("SCINTILLATIONRISETIME1", ttc.ScintillationRiseTimeConstant1());
    scintillatorPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", ttc.ScintillationDecayTimeConstant1());
    scintillatorPropertiesTable->AddConstProperty("RESOLUTIONSCALE", ttc.ResolutionScale());
    ttcScintillatorMaterial->SetMaterialPropertiesTable(scintillatorPropertiesTable);

    const auto lightCouplerPropertiesTable{new G4MaterialPropertiesTable};
    lightCouplerPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, ttc.LightCouplerRIndex()); // EJ-550
    lightCouplerPropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, ttc.LightCouplerAbsLength());
    lightCoupler->SetMaterialPropertiesTable(lightCouplerPropertiesTable);

    const auto windowPropertiesTable{new G4MaterialPropertiesTable};
    windowPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, ttc.WindowRIndex());
    window->SetMaterialPropertiesTable(windowPropertiesTable);

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, ttc.RfSurface());

    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, ttc.CouplerSurface());

    const auto airPaintSurfacePropertiesTable{new G4MaterialPropertiesTable};
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, ttc.AirPaintSurface());

    const auto cathodeSurfacePropertiesTable{new G4MaterialPropertiesTable};
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, ttc.CathodeSurface());
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", ttc.SiPMEnergyBin(), ttc.SiPMEfficiency());

    // Construct Detector
    int tileID{};
    const auto deltaPhi{2 * pi / ttc.NAlongPhi()};
    const auto nWidth{ssize(ttc.Width())};
    std::vector<G4LogicalVolume*> ttcAirBoxLogic;

    // set up the PCB
    const auto ttcPCBSolid{Make<G4Box>(
        "TTCPCBSolid",
        ttc.PCBWidth() / 2,
        ttc.PCBThickness() / 2,
        ttc.PCBLength() / 2)};
    const auto ttcPCBLogic{Make<G4LogicalVolume>(
        ttcPCBSolid,
        nistManager->FindOrBuildMaterial("G4_POLYCARBONATE"),
        "TTCPCB")};
    // set up the Window
    const auto ttcWindowSolid{Make<G4Box>(
        "TTCWindowSolid",
        ttc.WindowWidth() / 2,
        ttc.WindowThickness() / 2,
        ttc.WindowLength() / 2)};
    const auto ttcWindowUpLogic{Make<G4LogicalVolume>(
        ttcWindowSolid,
        window,
        "TTCWindowUp")};
    const auto ttcWindowDownLogic{Make<G4LogicalVolume>(
        ttcWindowSolid,
        window,
        "TTCWindowDown")};
    // set up the Silicon
    const auto ttcSiliconeSolid{Make<G4Box>(
        "TTCSiliconeSolid",
        ttc.SiliconeWidth() / 2,
        ttc.SiliconeThickness() / 2,
        ttc.SiliconeLength() / 2)};
    const auto ttcSiliconeLogic{Make<G4LogicalVolume>(
        ttcSiliconeSolid,
        nistManager->FindOrBuildMaterial("G4_Si"),
        "TTCSilicone")};
    // set up the LightCoupler
    const auto ttcLightCouplerSolid{Make<G4Box>(
        "TTCLightCouplerSolid",
        ttc.LightCouplerWidth() / 2,
        ttc.LightCouplerThickness() / 2,
        ttc.LightCouplerLength() / 2)};
    const auto ttcLightCouplerLogic{Make<G4LogicalVolume>(
        ttcLightCouplerSolid,
        lightCoupler,
        "TTCLightCoupler")};

    for (gsl::index i{}; i < nWidth; ++i) { // clang-format off
        //set up the empty air motherbox
        const auto ttcAirBoxSolid{Make<G4Box>(
            "TTCAirBoxSolid",
            ttc.PCBWidth() / 2,
            ttc.Length()/2 +ttc.PCBThickness()+ttc.WindowThickness()+ttc.LightCouplerThickness(),
            ttc.Width()[i] / 2)};
        const auto ttcAirBoxMaterial{G4Material::GetMaterial("G4_AIR")};
        ttcAirBoxLogic.push_back(Make<G4LogicalVolume>(ttcAirBoxSolid, ttcAirBoxMaterial,"TTCAirBox"));
        //set up the TTCscintillator
        const auto ttcScintillatorSolid{Make<G4Box>(
            "TTCScintillatorSolid", 
            ttc.Thickness() / 2,
            ttc.Length() / 2,
            ttc.Width()[i] / 2)};
        const auto ttcScintillatorLogic{Make<G4LogicalVolume>(
            ttcScintillatorSolid,
            ttcScintillatorMaterial,
            "TTCScintillator")};
        //set the position of air mother box
        const auto transform{G4RotateZ3D{Mustard::Math::IsEven(i) ? 0 : deltaPhi / 2} *
                            G4Translate3D{Mustard::VectorCast<G4ThreeVector>(ttc.Position()[i])} *
                            G4RotateZ3D{ttc.SlantAngle()}}; // clang-format on
        for (int j{}; j < ttc.NAlongPhi(); ++j, ++tileID) {
            Make<G4PVPlacement>(
                G4RotateZ3D{j * deltaPhi} * transform,
                ttcAirBoxLogic[i],
                "TTCAirBoxPhysics",
                Mother().LogicalVolume(),
                false,
                tileID,
                checkOverlaps);
        }
        // set the position of the TTC scintillator inside the air mother box
        auto ttcScintillatorPhysics{Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, 0, 0),
            ttcScintillatorLogic,
            "TTCScintillatorPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps)};
        // set the position of the LightCoupler inside the air mother box
        auto ttcLightCouplerUpPhysics{Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, (ttc.Length() + ttc.LightCouplerThickness()) / 2, 0),
            ttcLightCouplerLogic,
            "TTCLightCouplerPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps)};
        auto ttcLightCouplerDownPhysics{Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, -(ttc.Length() + ttc.LightCouplerThickness()) / 2, 0),
            ttcLightCouplerLogic,
            "TTCLightCouplerPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps)};
        // set the position of the Window inside the air mother box
        Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, ttc.LightCouplerThickness() + (ttc.Length() + ttc.WindowThickness()) / 2, 0),
            ttcWindowUpLogic,
            "TTCWindowPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps);
        Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, -(ttc.LightCouplerThickness() + (ttc.Length() + ttc.WindowThickness()) / 2), 0),
            ttcWindowDownLogic,
            "TTCWindowPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps);
        // set the position of the PCB inside the air mother box
        Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, ttc.WindowThickness() + ttc.LightCouplerThickness() + (ttc.Length() + ttc.PCBThickness()) / 2, 0),
            ttcPCBLogic,
            "TTCPCBPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps);
        Make<G4PVPlacement>(
            nullptr,
            G4ThreeVector(0, -(ttc.WindowThickness() + ttc.LightCouplerThickness() + (ttc.Length() + ttc.PCBThickness()) / 2), 0),
            ttcPCBLogic,
            "TTCPCBPhysics",
            ttcAirBoxLogic[i],
            false,
            checkOverlaps);

        // Construct Optical Surface
        const auto rfSurface{new G4OpticalSurface("reflector", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"reflectorSurface", ttcScintillatorLogic, rfSurface};
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);
        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        for (int k{}; k < ttc.NAlongPhi(); ++k) {
            new G4LogicalBorderSurface{"airPaintSurface",
                                       PhysicalVolume("TTCAirBoxPhysics", k + i * ttc.NAlongPhi()),
                                       ttcScintillatorPhysics,
                                       airPaintSurface};
            airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);
        }

        const auto couplerUpSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
        new G4LogicalBorderSurface{"couplerSurface",
                                   ttcScintillatorPhysics,
                                   ttcLightCouplerUpPhysics,
                                   couplerUpSurface};
        couplerUpSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        const auto couplerDownSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
        new G4LogicalBorderSurface{"couplerSurface",
                                   ttcScintillatorPhysics,
                                   ttcLightCouplerDownPhysics,
                                   couplerDownSurface};
        couplerDownSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
    }
    // set the position of the Silicon inside the Window
    Make<G4PVPlacement>(
        nullptr,
        G4ThreeVector(0, (ttc.SiliconeThickness() - ttc.WindowThickness()) / 2, 0),
        ttcSiliconeLogic,
        "TTCSiliconePhysics",
        ttcWindowUpLogic,
        false,
        checkOverlaps);
    Make<G4PVPlacement>(
        nullptr,
        G4ThreeVector(0, -(ttc.SiliconeThickness() - ttc.WindowThickness()) / 2, 0),
        ttcSiliconeLogic,
        "TTCSiliconePhysics",
        ttcWindowDownLogic,
        false,
        checkOverlaps);

    // Construct Silicon Optical Surface
    const auto cathodeSurface{new G4OpticalSurface("Cathode", unified, polished, dielectric_metal)};
    new G4LogicalSkinSurface{"cathodeSkinSurface", ttcSiliconeLogic, cathodeSurface};
    cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);
}

} // namespace MACE::Detector::Definition
