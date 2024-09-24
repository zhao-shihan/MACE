#include "MACE/Detector/Definition/ECalCrystal.h++"
#include "MACE/Detector/Definition/ECalPMTAssemblies.h++"
#include "MACE/Detector/Description/ECal.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

#include "G4Box.hh"
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
#include <map>
#include <utility>

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;
using namespace Mustard::PhysicalConstant;

auto ECalCrystal::Construct(G4bool checkOverlaps) -> void {
    const auto& eCal{Description::ECal::Instance()};
    const auto name{eCal.Name()};

    const auto innerRadius{eCal.InnerRadius()};
    const auto crystalHypotenuse{eCal.CrystalHypotenuse()};

    const auto scintillationWavelengthBin{eCal.ScintillationWavelengthBin()};
    const auto scintillationComponent1{eCal.ScintillationComponent1()};
    const auto scintillationYield{eCal.ScintillationYield()};
    const auto scintillationTimeConstant1{eCal.ScintillationTimeConstant1()};
    const auto resolutionScale{eCal.ResolutionScale()};

    const auto& vertex{eCal.Mesh().fVertex};
    const auto& faceList{eCal.Mesh().fFaceList};

    /////////////////////////////////////////////
    // Construct Element and Material
    /////////////////////////////////////////////

    const auto nistManager{G4NistManager::Instance()};

    const auto iodideElement{nistManager->FindOrBuildElement("I")};
    const auto cesiumElement{nistManager->FindOrBuildElement("Cs")};
    const auto thalliumElement{nistManager->FindOrBuildElement("Tl")};

    const auto csI{new G4Material("CsI", 4.51_g_cm3, 3, kStateSolid)};
    csI->AddElement(cesiumElement, 0.507556);
    csI->AddElement(iodideElement, 0.484639);
    csI->AddElement(thalliumElement, 0.007805);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    constexpr auto fLambdaMin{200_nm};
    constexpr auto fLambdaMax{700_nm};
    const std::vector<G4double> fEnergyPair{h_Planck * c_light / fLambdaMax,
                                            h_Planck * c_light / fLambdaMin};

    const auto csiPropertiesTable{new G4MaterialPropertiesTable};
    csiPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.79, 1.79});
    csiPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {370_mm, 370_mm});
    csiPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", scintillationWavelengthBin, scintillationComponent1);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", scintillationYield);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintillationTimeConstant1);
    csiPropertiesTable->AddConstProperty("RESOLUTIONSCALE", resolutionScale);
    csI->SetMaterialPropertiesTable(csiPropertiesTable);

    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        csiPropertiesTable->DumpTable();
    }

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0.985, 0.985});

    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

    const auto airPaintSurfacePropertiesTable{new G4MaterialPropertiesTable};
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0, 0});

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    for (int moduleID{};
         auto&& [centroid, _, vertexIndex] : std::as_const(faceList)) { // loop over all ECal face

        if(unitID != 213){
            unitID++;
            continue;
        }

        const auto centroidMagnitude{centroid.mag()};
        const auto crystalLength{crystalHypotenuse * centroidMagnitude};
        const auto outerHypotenuse{innerRadius + crystalHypotenuse};

        const auto MakeTessellatedSolid{
            [&, &centroid = centroid, &vertexIndex = vertexIndex](const auto& name) {
                constexpr auto crystalHypotenuseExtension = 1_cm;

                const auto innerHypotenuseHere{innerRadius - crystalHypotenuseExtension};
                const auto innerCentroidHere{innerHypotenuseHere * centroid};
                std::vector<G4ThreeVector> innerVertexHere(vertexIndex.size());
                std::ranges::transform(vertexIndex, innerVertexHere.begin(),
                                       [&](const auto& i) { return innerHypotenuseHere * vertex[i]; });
                const auto outerHypotenuseHere{outerHypotenuse + crystalHypotenuseExtension};
                const auto outerCentroidHere{outerHypotenuseHere * centroid};
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

                const auto solid{Make<G4TessellatedSolid>(name)};
                // inner surface
                solid->AddFacet(new G4TriangularFacet{innerCentroidHere,
                                                      innerVertexHere[0],
                                                      innerVertexHere[vertexIndex.size() - 1],
                                                      G4FacetVertexType::ABSOLUTE});
                for (auto i{std::ssize(vertexIndex) - 1}; i > 0; --i) {
                    solid->AddFacet(new G4TriangularFacet{innerCentroidHere,
                                                          innerVertexHere[i],
                                                          innerVertexHere[i - 1],
                                                          G4FacetVertexType::ABSOLUTE});
                }
                // side surface
                for (int i{}; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4QuadrangularFacet{innerVertexHere[i],
                                                            innerVertexHere[i + 1],
                                                            outerVertexHere[i + 1],
                                                            outerVertexHere[i],
                                                            G4FacetVertexType::ABSOLUTE});
                }
                solid->AddFacet(new G4QuadrangularFacet{innerVertexHere[vertexIndex.size() - 1],
                                                        innerVertexHere[0],
                                                        outerVertexHere[0],
                                                        outerVertexHere[vertexIndex.size() - 1],
                                                        G4FacetVertexType::ABSOLUTE});
                // outer surface
                for (int i{}; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4TriangularFacet{outerCentroidHere,
                                                          outerVertexHere[i],
                                                          outerVertexHere[i + 1],
                                                          G4FacetVertexType::ABSOLUTE});
                }
                solid->AddFacet(new G4TriangularFacet{outerCentroidHere,
                                                      outerVertexHere[vertexIndex.size() - 1],
                                                      outerVertexHere[0],
                                                      G4FacetVertexType::ABSOLUTE});
                solid->SetSolidClosed(true);
                return solid;
            }};

        const auto crystalTransform{eCal.ComputeTransformToOuterSurfaceWithOffset(moduleID,
                                                                                  -crystalLength / 2)};

        // Crystal

        const auto solidCrystal{MakeTessellatedSolid(fmt::format("temp_{}", moduleID))};
        const auto cutCrystalBox{
            Make<G4Box>(
                "temp",
                1_m,
                1_m,
                crystalLength / 2)};
        const auto cutSolidCrystal{
            Make<G4IntersectionSolid>(
                "ECalCrystal",
                solidCrystal,
                cutCrystalBox,
                crystalTransform)};
        const auto logicCrystal{
            Make<G4LogicalVolume>(
                cutSolidCrystal,
                csI,
                "ECalCrystal")};
        const auto physicalCrystal{
            Make<G4PVPlacement>(
                G4Transform3D{},
                logicCrystal,
                fmt::format("ECalCrystal_{}", moduleID),
                Mother().LogicalVolume(),
                true,
                moduleID,
                checkOverlaps)};

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto rfSurface{new G4OpticalSurface("reflector", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"reflectorSurface", logicCrystal, rfSurface};
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        new G4LogicalBorderSurface{"airPaintSurface", Mother().PhysicalVolume(), physicalCrystal, airPaintSurface};
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);

        const auto eCalPMTCoupler{FindSibling<ECalPMTAssemblies>()};
        if (eCalPMTCoupler) {
            const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
            new G4LogicalBorderSurface{"couplerSurface",
                                       physicalCrystal,
                                       eCalPMTCoupler->PhysicalVolume("ECalPMTCoupler", moduleID),
                                       couplerSurface};
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        ++moduleID;
    }
}

} // namespace MACE::Detector::Definition
