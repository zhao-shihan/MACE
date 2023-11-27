#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTWindow.h++"
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

void EMCPMTWindow::Construct(G4bool checkOverlaps) {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto pmtCouplerThickness = description.PMTCouplerThickness();
    const auto pmtWindowThickness = description.PMTWindowThickness();

    /////////////////////////////////////////////
    // Define Element and Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();
    const auto oxygenElement = nistManager->FindOrBuildElement("O");
    const auto siliconElement = nistManager->FindOrBuildElement("Si");

    const auto glass = new G4Material("Quartz", 2.64_g_cm3, 2, kStateSolid);
    glass->AddElement(oxygenElement, 0.532570);
    glass->AddElement(siliconElement, 0.467430);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                               h_Planck * c_light / fLambdaMin};

    const auto windowPropertiesTable = new G4MaterialPropertiesTable();
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.54, 1.54});
    glass->SetMaterialPropertiesTable(windowPropertiesTable);

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    const auto& emc = Description::EMC::Instance();
    const auto& faceList = emc.Mesh().fFaceList;

    for (G4int copyNo = 0;
         auto&& [centroid, normal, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face

        const auto windowTransform =
            Detector::Description::EMC::Instance().ComputeTransformToOuterSurfaceWithOffset(copyNo,
                                                                                            pmtCouplerThickness + pmtWindowThickness / 2);

        assert(vertexIndex.size() == 5 or vertexIndex.size() == 6);
        const auto pmtRadius = vertexIndex.size() == 5 ? emc.SmallPMTCathodeRadius() : emc.LargePMTCathodeRadius();

        const auto solidWindow = Make<G4Tubs>("temp", 0, pmtRadius, pmtWindowThickness / 2, 0, 2 * pi);
        const auto logicWindow = Make<G4LogicalVolume>(solidWindow, glass, "EMCPMTWindow");
        Make<G4PVPlacement>(windowTransform,
                            logicWindow,
                            "EMCPMTWindow",
                            Mother().LogicalVolume().get(),
                            true,
                            copyNo,
                            checkOverlaps);

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry::Fast
