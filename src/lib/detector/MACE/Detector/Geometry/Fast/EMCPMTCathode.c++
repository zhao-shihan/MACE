#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCathode.h++"
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
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

#include <algorithm>
#include <utility>

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

void EMCPMTCathode::Construct(G4bool checkOverlaps) {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto innerRadius = description.InnerRadius();
    const auto fCrystalHypotenuse = description.CrystalHypotenuse();

    double pmtRadius;
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

    const auto bialkali = new G4Material("Bialkali", 2.0_g_cm3, 3, kStateSolid);
    bialkali->AddElement(potassiumElement, 2);
    bialkali->AddElement(cesiumElement, 1);
    bialkali->AddElement(antimonyElement, 1);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    const auto fLambdaMin = 200_nm;
    const auto fLambdaMax = 700_nm;
    std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                         h_Planck * c_light / fLambdaMin};

    std::vector<G4double> cathodeSurfacePropertiesEnergy(pmtWaveLengthBin.size());
    std::vector<G4double> cathodeSurfacePropertiesEfficiency(pmtQuantumEfficiency.size());
    std::transform(pmtWaveLengthBin.begin(), pmtWaveLengthBin.end(), cathodeSurfacePropertiesEnergy.begin(),
                   [](auto val) { return h_Planck * c_light / (val * nm / mm); });
    std::transform(pmtQuantumEfficiency.begin(), pmtQuantumEfficiency.end(), cathodeSurfacePropertiesEfficiency.begin(),
                   [](auto n) { return n * perCent; });

    auto cathodeSurfacePropertiesTable = new G4MaterialPropertiesTable();
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);

    if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VerboseLevel::Verbose) {
        cathodeSurfacePropertiesTable->DumpTable();
    }

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    const auto& emc = Description::EMC::Instance();
    const auto& vertex = emc.Mesh().fVertex;
    const auto& faceList = emc.Mesh().fFaceList;

    for (G4int copyNo = 0;
         auto&& [centroid, normal, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face
        const auto centroidMagnitude = centroid.mag();
        auto fCrystalLength = fCrystalHypotenuse * centroidMagnitude;

        const auto crytalInnerHypotenuse = innerRadius;
        const auto outerHypotenuse = crytalInnerHypotenuse + fCrystalHypotenuse;

        const auto crystalOuterRadius = outerHypotenuse * centroidMagnitude;
        const auto outerRadius = outerHypotenuse * centroidMagnitude;

        const auto Transform =
            [&normal,
             crystalOuterCentroid = crystalOuterRadius * centroid / centroidMagnitude,
             rotation = G4Rotate3D{normal.theta(), CLHEP::HepZHat.cross(normal)}](double offsetInNormalDirection) {
                return G4Translate3D{crystalOuterCentroid + offsetInNormalDirection * normal} * rotation;
            };

        if (copyNo <= 11) {
            pmtRadius = 23_mm;
        } else {
            pmtRadius = 36_mm;
        }

        const auto solidCathode = Make<G4Tubs>("temp", 0, pmtRadius, pmtCathodeThickness / 2, 0, 2 * pi);
        const auto logicCathode = Make<G4LogicalVolume>(solidCathode, bialkali, "EMCCathode");
        const auto cathodeTransform = Transform(pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2);
        const auto physicalCathode = Make<G4PVPlacement>(cathodeTransform,
                                                         logicCathode,
                                                         "EMCCathode",
                                                         Mother().LogicalVolume().get(),
                                                         true,
                                                         copyNo,
                                                         checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        auto cathodeSurface = new G4OpticalSurface("Cathode", unified, polished, dielectric_metal);
        new G4LogicalSkinSurface("cathodeSkinSurface", logicCathode, cathodeSurface);
        cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry::Fast