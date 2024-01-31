#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCPMTCoupler.h++"
#include "MACE/Detector/Description/EMC.h++"
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

namespace MACE::Detector::Definition {

using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

auto EMCPMTCoupler::Construct(G4bool checkOverlaps) -> void {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto pmtCouplerThickness = description.PMTCouplerThickness();

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();
    const auto hydrogenElement = nistManager->FindOrBuildElement("H");
    const auto carbonElement = nistManager->FindOrBuildElement("C");
    const auto oxygenElement = nistManager->FindOrBuildElement("O");
    const auto siliconElement = nistManager->FindOrBuildElement("Si");

    const auto siliconeGrease = new G4Material("siliconeGrease", 1.06_g_cm3, 4, kStateLiquid);
    siliconeGrease->AddElement(carbonElement, 2);
    siliconeGrease->AddElement(hydrogenElement, 6);
    siliconeGrease->AddElement(oxygenElement, 1);
    siliconeGrease->AddElement(siliconElement, 1);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                               h_Planck * c_light / fLambdaMin};

    const auto siliconeGreasePropertiesTable = new G4MaterialPropertiesTable();
    siliconeGreasePropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.46, 1.46}); // EJ-550
    siliconeGreasePropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {100_cm, 100_cm});
    siliconeGrease->SetMaterialPropertiesTable(siliconeGreasePropertiesTable);

    const auto couplerSurfacePropertiesTable = new G4MaterialPropertiesTable();
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

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
        const auto logicOptocoupler = Make<G4LogicalVolume>(solidOptocoupler, siliconeGrease, "EMCPMTCoupler");
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

        const auto emcCrystal{FindSibling<EMCPMTCoupler>()};
        if (emcCrystal) {
            const auto couplerSurface = new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric);
            new G4LogicalBorderSurface("couplerSurface",
                                       emcCrystal->PhysicalVolume(copyNo).get(),
                                       physicalOptocoupler,
                                       couplerSurface);
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        ++copyNo;
    }
}

} // namespace MACE::Detector::Definition
