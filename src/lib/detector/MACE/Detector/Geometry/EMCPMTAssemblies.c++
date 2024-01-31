#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/EMCPMTAssemblies.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
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

namespace MACE::Detector::Geometry {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

auto EMCPMTAssemblies::Construct(G4bool checkOverlaps) -> void {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto pmtCouplerThickness = description.PMTCouplerThickness();
    const auto pmtWindowThickness = description.PMTWindowThickness();
    const auto pmtCathodeThickness = description.PMTCathodeThickness();

    const auto pmtWaveLengthBin = description.PMTWaveLengthBin();
    const auto pmtQuantumEfficiency = description.PMTQuantumEfficiency();

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();
    const auto potassiumElement = nistManager->FindOrBuildElement("K");
    const auto antimonyElement = nistManager->FindOrBuildElement("Sb");
    const auto cesiumElement = nistManager->FindOrBuildElement("Cs");

    const auto glass = nistManager->FindOrBuildMaterial("G4_GLASS_PLATE");
    const auto bialkali = new G4Material("Bialkali", 2.0_g_cm3, 3, kStateSolid);
    bialkali->AddElement(potassiumElement, 2);
    bialkali->AddElement(cesiumElement, 1);
    bialkali->AddElement(antimonyElement, 1);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                               h_Planck * c_light / fLambdaMin};

    const auto windowPropertiesTable = new G4MaterialPropertiesTable();
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.49, 1.49}); // ET 9269B 9956B
    glass->SetMaterialPropertiesTable(windowPropertiesTable);

    std::vector<G4double> cathodeSurfacePropertiesEnergy(pmtWaveLengthBin.size());
    std::vector<G4double> cathodeSurfacePropertiesEfficiency(pmtQuantumEfficiency.size());
    std::transform(pmtWaveLengthBin.begin(), pmtWaveLengthBin.end(), cathodeSurfacePropertiesEnergy.begin(),
                   [](auto val) { return h_Planck * c_light / (val * nm / mm); });
    std::transform(pmtQuantumEfficiency.begin(), pmtQuantumEfficiency.end(), cathodeSurfacePropertiesEfficiency.begin(),
                   [](auto n) { return n * perCent; });

    const auto cathodeSurfacePropertiesTable = new G4MaterialPropertiesTable();
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);

    if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VL::Verbose) {
        fmt::println("\nPMT Quantum Efficiency:");
        cathodeSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    const auto& emc = Description::EMC::Instance();
    const auto& faceList = emc.Mesh().fFaceList;

    for (G4int copyNo = 0;
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face

        double cathodeRadius{};
        double pmtRadius{};
        double pmtLength{};

        if (vertexIndex.size() == 5) {
            pmtRadius = emc.SmallPMTRadius();
            pmtLength = emc.SmallPMTLength();
            cathodeRadius = emc.SmallPMTCathodeRadius();
        } else if (vertexIndex.size() == 6) {
            pmtRadius = emc.LargePMTRadius();
            pmtLength = emc.LargePMTLength();
            cathodeRadius = emc.LargePMTCathodeRadius();
        }

        const auto shellTransform =
            Detector::Description::EMC::Instance().ComputeTransformToOuterSurfaceWithOffset(copyNo,
                                                                                            pmtCouplerThickness + pmtLength / 2);
        const auto cathodeTransform =
            Detector::Description::EMC::Instance().ComputeTransformToOuterSurfaceWithOffset(copyNo,
                                                                                            pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2);

        const auto solidGlassBox = Make<G4Tubs>("temp", 0, pmtRadius, pmtLength / 2, 0, 2 * pi);
        const auto solidPMTVacuum = Make<G4Tubs>("temp", 0, pmtRadius - pmtWindowThickness, pmtLength / 2 - pmtWindowThickness, 0, 2 * pi);
        const auto solidPMTShell = Make<G4SubtractionSolid>("EMCPMTShell", solidGlassBox, solidPMTVacuum);
        const auto logicPMTShell = Make<G4LogicalVolume>(solidPMTShell, glass, "EMCPMTShell");
        Make<G4PVPlacement>(shellTransform,
                            logicPMTShell,
                            "EMCPMTShell",
                            Mother().LogicalVolume().get(),
                            true,
                            copyNo,
                            checkOverlaps);

        const auto solidCathode = Make<G4Tubs>("temp", 0, cathodeRadius, pmtCathodeThickness / 2, 0, 2 * pi);
        const auto logicCathode = Make<G4LogicalVolume>(solidCathode, bialkali, "EMCPMTCathode");

        Make<G4PVPlacement>(cathodeTransform,
                            logicCathode,
                            "EMCPMTCathode",
                            Mother().LogicalVolume().get(),
                            true,
                            copyNo,
                            checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto cathodeSurface = new G4OpticalSurface("Cathode", unified, polished, dielectric_metal);
        new G4LogicalSkinSurface("cathodeSkinSurface", logicCathode, cathodeSurface);
        cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry
