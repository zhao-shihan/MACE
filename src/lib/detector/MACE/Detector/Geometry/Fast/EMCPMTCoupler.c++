#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
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
#include "G4Tubs.hh"

#include <algorithm>
#include <utility>

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

void EMCPMTCoupler::Construct(G4bool checkOverlaps) {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto innerRadius = description.InnerRadius();
    const auto fCrystalHypotenuse = description.CrystalHypotenuse();

    double pmtRadius;
    const auto pmtCouplerThickness = description.PMTCouplerThickness();

    const auto couplerEnergyBin = description.CouplerEnergyBin();
    const auto couplerRefractiveIndex = description.CouplerRefractiveIndex();

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();
    const auto hydrogenElement = nistManager->FindOrBuildElement("H");
    const auto carbonElement = nistManager->FindOrBuildElement("C");
    const auto oxygenElement = nistManager->FindOrBuildElement("O");
    const auto siliconElement = nistManager->FindOrBuildElement("Si");

    const auto siliconeOil = new G4Material("silicone_oil", 0.97_g_cm3, 4, kStateLiquid);
    siliconeOil->AddElement(carbonElement, 2);
    siliconeOil->AddElement(hydrogenElement, 6);
    siliconeOil->AddElement(oxygenElement, 1);
    siliconeOil->AddElement(siliconElement, 1);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    const auto fLambdaMin = 200_nm;
    const auto fLambdaMax = 700_nm;
    std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                         h_Planck * c_light / fLambdaMin};

    auto siliconeOilPropertiesTable = new G4MaterialPropertiesTable();
    siliconeOilPropertiesTable->AddProperty("RINDEX", couplerEnergyBin, couplerRefractiveIndex);
    siliconeOilPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {15_cm, 15_cm});
    siliconeOil->SetMaterialPropertiesTable(siliconeOilPropertiesTable);

    if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VerboseLevel::Verbose) {
        siliconeOilPropertiesTable->DumpTable();
    }

    auto rfSurfacePropertiesTable = new G4MaterialPropertiesTable();
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0.985, 0.985});

    auto rfoilSurfacePropertiesTable = new G4MaterialPropertiesTable();
    rfoilSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

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
            pmtRadius = 25.5_mm;
        } else {
            pmtRadius = 40_mm;
        }

        const auto solidOptocoupler = Make<G4Tubs>("temp", 0, pmtRadius, pmtCouplerThickness / 2, 0, 2 * pi);
        const auto logicOptocoupler = Make<G4LogicalVolume>(solidOptocoupler, siliconeOil, "EMCOptocoupler");
        const auto optocouplerTransform = Transform(pmtCouplerThickness / 2);
        const auto physicalOptocoupler = Make<G4PVPlacement>(optocouplerTransform,
                                                             logicOptocoupler,
                                                             "EMCOptocoupler",
                                                             Mother().LogicalVolume().get(),
                                                             true,
                                                             copyNo,
                                                             checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        auto optocouplerSurface = new G4OpticalSurface("Optocoupler", unified, polished, dielectric_metal);
        new G4LogicalBorderSurface("optocouplerSurface", physicalOptocoupler, Mother().PhysicalVolume().get(), optocouplerSurface);
        optocouplerSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        if (FindSibling<EMCCrystal>().has_value() == true) {

            auto rfoilSurface = new G4OpticalSurface("rfoil", unified, polished, dielectric_dielectric);
            new G4LogicalBorderSurface("rfoilSurface",
                                       FindSibling<EMCCrystal>().value().get().PhysicalVolume(copyNo).get(),
                                       physicalOptocoupler,
                                       rfoilSurface);
            rfoilSurface->SetMaterialPropertiesTable(rfoilSurfacePropertiesTable);
        }

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry::Fast