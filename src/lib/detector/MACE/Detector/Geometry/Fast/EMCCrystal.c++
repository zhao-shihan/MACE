#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4IntersectionSolid.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4QuadrangularFacet.hh"
#include "G4TessellatedSolid.hh"

#include "fmt/format.h"

#include <algorithm>
#include <utility>

namespace MACE::Detector::Geometry::Fast {

// using namespace MathConstant;
using namespace LiteralUnit;
using namespace MathConstant;
using namespace PhysicalConstant;

auto EMCCrystal::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();

    const auto innerRadius = description.InnerRadius();
    const auto crystalHypotenuse = description.CrystalHypotenuse();

    const auto csiEnergyBin = description.CsIEnergyBin();
    const auto csiScintillationComponent1 = description.CsIScintillationComponent1();
    const auto scintillationYield = description.ScintillationYield();
    const auto scintillationTimeConstant1 = description.ScintillationTimeConstant1();
    const auto resolutionScale = description.ResolutionScale();

    const auto& emcCrystal = Description::EMC::Instance();
    const auto& vertex = emcCrystal.Mesh().fVertex;
    const auto& faceList = emcCrystal.Mesh().fFaceList;

    /////////////////////////////////////////////
    // Construct Element and Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();

    const auto iodideElement = nistManager->FindOrBuildElement("I");
    const auto cesiumElement = nistManager->FindOrBuildElement("Cs");
    const auto thaliumElement = nistManager->FindOrBuildElement("Tl");

    const auto csI = new G4Material("CsI", 4.51_g_cm3, 3, kStateSolid);
    csI->AddElement(cesiumElement, 0.507556);
    csI->AddElement(iodideElement, 0.484639);
    csI->AddElement(thaliumElement, 0.007805);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin = 200_nm;
    constexpr auto fLambdaMax = 700_nm;
    const std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                               h_Planck * c_light / fLambdaMin};

    const auto csiPropertiesTable = new G4MaterialPropertiesTable;
    csiPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.79, 1.79});
    csiPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {370_mm, 370_mm});
    csiPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", csiEnergyBin, csiScintillationComponent1);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", scintillationYield);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintillationTimeConstant1);
    csiPropertiesTable->AddConstProperty("RESOLUTIONSCALE", resolutionScale);
    csI->SetMaterialPropertiesTable(csiPropertiesTable);

    if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VL::Verbose) {
        fmt::println("\nPMT Quantum Efficiency:");
        csiPropertiesTable->DumpTable();
    }

    const auto rfSurfacePropertiesTable = new G4MaterialPropertiesTable();
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0.985, 0.985});

    const auto couplerSurfacePropertiesTable = new G4MaterialPropertiesTable();
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

    const auto airPaintSurfacePropertiesTable = new G4MaterialPropertiesTable();
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0, 0});

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    for (G4int copyNo = 0;
         auto&& [centroid, _, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face
        const auto centroidMagnitude = centroid.mag();
        const auto crystalLength = crystalHypotenuse * centroidMagnitude;
        const auto outerHypotenuse = innerRadius + crystalHypotenuse;

        // make a crystal-shaped solid with certain shrinkage (e.g. shrink with coat thickness)

        const auto MakeTessellatedSolid =
            [&, &centroid = centroid, &vertexIndex = vertexIndex](const auto& name) {
                constexpr auto crystalHypotenuseExtension = 1_cm;

                const auto innerHypotenuseHere = innerRadius - crystalHypotenuseExtension;
                const auto innerCentroidHere = innerHypotenuseHere * centroid;
                std::vector<G4ThreeVector> innerVertexHere(vertexIndex.size());
                std::ranges::transform(vertexIndex, innerVertexHere.begin(),
                                       [&](const auto& i) { return innerHypotenuseHere * vertex[i]; });
                const auto outerHypotenuseHere = outerHypotenuse + crystalHypotenuseExtension;
                const auto outerCentroidHere = outerHypotenuseHere * centroid;
                std::vector<G4ThreeVector> outerVertexHere(vertexIndex.size());
                std::ranges::transform(vertexIndex, outerVertexHere.begin(),
                                       [&](const auto& i) { return outerHypotenuseHere * vertex[i]; });

                // clang-format off

                /* Pentagon:
                 *      0
                 *   /  |  \
                 *  1 - C - 4
                 *  \ / \  /
                 *   2 - 3
                 *
                 * Hexagon:
                 *     0 - 5
                 *   / \  / \
                 *  1 - C - 4
                 *  \ /  \ /
                 *   2 - 3
                 */
                // clang-format on

                const auto solid = Make<G4TessellatedSolid>(name);
                // inner surface
                solid->AddFacet(new G4TriangularFacet(innerCentroidHere,
                                                      innerVertexHere[0],
                                                      innerVertexHere[vertexIndex.size() - 1],
                                                      G4FacetVertexType::ABSOLUTE));
                for (auto i = std::ssize(vertexIndex) - 1; i > 0; --i) {
                    solid->AddFacet(new G4TriangularFacet(innerCentroidHere,
                                                          innerVertexHere[i],
                                                          innerVertexHere[i - 1],
                                                          G4FacetVertexType::ABSOLUTE));
                }
                // side surface
                for (auto i = 0; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4QuadrangularFacet(innerVertexHere[i],
                                                            innerVertexHere[i + 1],
                                                            outerVertexHere[i + 1],
                                                            outerVertexHere[i],
                                                            G4FacetVertexType::ABSOLUTE));
                }
                solid->AddFacet(new G4QuadrangularFacet(innerVertexHere[vertexIndex.size() - 1],
                                                        innerVertexHere[0],
                                                        outerVertexHere[0],
                                                        outerVertexHere[vertexIndex.size() - 1],
                                                        G4FacetVertexType::ABSOLUTE));
                // outer surface
                for (auto i = 0; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4TriangularFacet(outerCentroidHere,
                                                          outerVertexHere[i],
                                                          outerVertexHere[i + 1],
                                                          G4FacetVertexType::ABSOLUTE));
                }
                solid->AddFacet(new G4TriangularFacet(outerCentroidHere,
                                                      outerVertexHere[vertexIndex.size() - 1],
                                                      outerVertexHere[0],
                                                      G4FacetVertexType::ABSOLUTE));
                solid->SetSolidClosed(true);
                return solid;
            };

        const auto crystalTransform =
            Detector::Description::EMC::Instance().ComputeTransformToOuterSurfaceWithOffset(copyNo,
                                                                                            -crystalLength / 2);

        // Crystal

        const auto solidCrystal = MakeTessellatedSolid(fmt::format("temp{}", copyNo));
        const auto cutCrystalBox = Make<G4Box>("temp", 1_m, 1_m, crystalLength / 2);
        const auto cutSoildCrystal = Make<G4IntersectionSolid>("EMCCrystal", solidCrystal, cutCrystalBox, crystalTransform);
        //========================================== CsI(Tl) ============================================
        const auto logicCrystal = Make<G4LogicalVolume>(cutSoildCrystal, csI, "EMCCrystal");
        //===============================================================================================
        const auto physicalCrystal = Make<G4PVPlacement>(G4Transform3D{},
                                                         logicCrystal,
                                                         "EMCCrystal",
                                                         Mother().LogicalVolume().get(),
                                                         true,
                                                         copyNo,
                                                         checkOverlaps);

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto rfSurface = new G4OpticalSurface("reflector", unified, polished, dielectric_dielectric);
        new G4LogicalSkinSurface("reflectorSurface", logicCrystal, rfSurface);
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto airPaintSurface = new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal);
        new G4LogicalBorderSurface("airPaintSurface", Mother().PhysicalVolume().get(), physicalCrystal, airPaintSurface);
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);

        if (FindSibling<EMCPMTCoupler>().has_value() == true) {

            const auto couplerSurface = new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric);
            new G4LogicalBorderSurface("couplerSurface",
                                       physicalCrystal,
                                       FindSibling<EMCPMTCoupler>().value().get().PhysicalVolume(copyNo).get(),
                                       couplerSurface);
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        ++copyNo;
    }
}

} // namespace MACE::Detector::Geometry::Fast
