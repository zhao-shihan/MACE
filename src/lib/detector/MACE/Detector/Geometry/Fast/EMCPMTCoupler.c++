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
#include <cassert>
#include <utility>

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

void EMCPMTCoupler::Construct(G4bool checkOverlaps) {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

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

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                               h_Planck * c_light / fLambdaMin};

    const auto siliconeOilPropertiesTable = new G4MaterialPropertiesTable();
    siliconeOilPropertiesTable->AddProperty("RINDEX", couplerEnergyBin, couplerRefractiveIndex);
    siliconeOilPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {15_cm, 15_cm});
    siliconeOil->SetMaterialPropertiesTable(siliconeOilPropertiesTable);

    const auto rfcpSurfacePropertiesTable = new G4MaterialPropertiesTable();
    rfcpSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    const auto& emc = Description::EMC::Instance();
    const auto& faceList = emc.Mesh().fFaceList;

    for (G4int copyNo = 0;
         auto&& [_1, _2, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face

        const auto optocouplerTransform =
            Detector::Description::EMC::Instance().ComputeTransformToOuterSurfaceWithOffset(copyNo,
                                                                                            pmtCouplerThickness / 2);

        assert(vertexIndex.size() == 5 or vertexIndex.size() == 6);
        const auto pmtRadius = vertexIndex.size() == 5 ? emc.SmallPMTRadius() : emc.LargePMTRadius();

        const auto solidOptocoupler = Make<G4Tubs>("temp", 0, pmtRadius, pmtCouplerThickness / 2, 0, 2 * pi);
        const auto logicOptocoupler = Make<G4LogicalVolume>(solidOptocoupler, siliconeOil, "EMCPMTCoupler");
        const auto physicalOptocoupler = Make<G4PVPlacement>(optocouplerTransform,
                                                             logicOptocoupler,
                                                             "EMCPMTCoupler",
                                                             Mother().LogicalVolume().get(),
                                                             true,
                                                             copyNo,
                                                             checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        if (FindSibling<EMCCrystal>().has_value() == true) {

            const auto rfoilSurface = new G4OpticalSurface("rfoil", unified, polished, dielectric_dielectric);
            new G4LogicalBorderSurface("rfoilSurface",
                                       FindSibling<EMCCrystal>().value().get().PhysicalVolume(copyNo).get(),
                                       physicalOptocoupler,
                                       rfoilSurface);
            rfoilSurface->SetMaterialPropertiesTable(rfcpSurfacePropertiesTable);
        }

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry::Fast
