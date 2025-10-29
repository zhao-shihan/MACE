#include "MACE/Detector/Definition/ECALCrystal.h++"
#include "MACE/Detector/Definition/ECALPhotoSensor.h++"
#include "MACE/Detector/Description/ECAL.h++"

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

namespace {
auto ComputeIntersection(G4ThreeVector vertexPlane, G4ThreeVector normPlane, G4ThreeVector vertexLine, G4ThreeVector direcLine) -> G4ThreeVector {
    double lambda{
        normPlane.dot(vertexPlane - vertexLine) / normPlane.dot(direcLine)};
    return vertexLine + direcLine * lambda;
}
} // namespace

auto ECALCrystal::Construct(G4bool checkOverlaps) -> void {
    const auto& ecal{Description::ECAL::Instance()};
    const auto name{ecal.Name()};

    const auto innerRadius{ecal.InnerRadius()};
    const auto crystalHypotenuse{ecal.CrystalHypotenuse()};

    const auto& vertex{ecal.Mesh().fVertex};
    const auto& faceList{ecal.Mesh().fFaceList};

    const auto& moduleSelection{ecal.ModuleSelection()};

    /////////////////////////////////////////////
    // Construct Element and Material
    /////////////////////////////////////////////

    const auto nist{G4NistManager::Instance()};

    const auto oxygenElement = nist->FindOrBuildElement("O");
    const auto siliconElement = nist->FindOrBuildElement("Si");
    const auto iodideElement{nist->FindOrBuildElement("I")};
    const auto cesiumElement{nist->FindOrBuildElement("Cs")};
    const auto thalliumElement{nist->FindOrBuildElement("Tl")};
    const auto yttriumElement = nist->FindOrBuildElement("Y");
    const auto lutetiumElement = nist->FindOrBuildElement("Lu");

    const auto csI{new G4Material("CsI", 4.51_g_cm3, 3, kStateSolid)};
    csI->AddElement(cesiumElement, 0.507556);
    csI->AddElement(iodideElement, 0.484639);
    csI->AddElement(thalliumElement, 0.007805);

    // const auto bgo{nist->FindOrBuildMaterial("G4_BGO")};

    const auto lyso = new G4Material("LYSO", 7.1_g_cm3, 5, kStateSolid);
    lyso->AddElement(oxygenElement, 0.175801);
    lyso->AddElement(siliconElement, 0.061720);
    lyso->AddElement(yttriumElement, 0.019538);
    lyso->AddElement(lutetiumElement, 0.730562);
    lyso->AddElement(cesiumElement, 0.012379);

    //////////////////////////////////////////////////
    // Construct Material Optical Properties Tables
    //////////////////////////////////////////////////

    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(ecal.ScintillationEnergyBin())};
    const auto crystalPropertiesTable{new G4MaterialPropertiesTable};
    crystalPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.79, 1.79});
    crystalPropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {370_mm, 370_mm});
    crystalPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", ecal.ScintillationEnergyBin(), ecal.ScintillationComponent1());
    crystalPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", ecal.ScintillationYield());
    crystalPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", ecal.ScintillationTimeConstant1());
    crystalPropertiesTable->AddConstProperty("RESOLUTIONSCALE", ecal.ResolutionScale());
    csI->SetMaterialPropertiesTable(crystalPropertiesTable);

    if (Mustard::Env::VerboseLevelReach<'V'>()) {
        crystalPropertiesTable->DumpTable();
    }

    const auto rfSurfacePropertiesTable{new G4MaterialPropertiesTable};
    rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0.99, 0.99});

    const auto couplerSurfacePropertiesTable{new G4MaterialPropertiesTable};
    couplerSurfacePropertiesTable->AddProperty("TRANSMITTANCE", {minPhotonEnergy, maxPhotonEnergy}, {1, 1});

    const auto airPaintSurfacePropertiesTable{new G4MaterialPropertiesTable};
    airPaintSurfacePropertiesTable->AddProperty("REFLECTIVITY", {minPhotonEnergy, maxPhotonEnergy}, {0, 0});

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////

    for (int moduleID{};
         auto&& [centroid, normal, vertexIndex] : std::as_const(faceList)) {
        // loop over all ECAL face
        // centroid here refer to the face 'center' of normalized ball

        if ((not moduleSelection.empty()) and std::ranges::find(moduleSelection, moduleID) == moduleSelection.end()) {
            moduleID++;
            continue;
        }

        const auto solidCrystal{
            [&, &centroid = centroid, &vertexIndex = vertexIndex](const auto& name) {
                const auto innerCentroid{innerRadius * centroid};
                std::vector<G4ThreeVector> innerVertex(vertexIndex.size());
                std::ranges::transform(vertexIndex, innerVertex.begin(),
                                       [&](const auto& i) { return ComputeIntersection(innerCentroid, normal, vertex[i], vertex[i]); });
                const auto outerRadius{innerRadius + crystalHypotenuse};
                const auto outerCentroid{outerRadius * centroid};
                std::vector<G4ThreeVector> outerVertex(vertexIndex.size());
                std::ranges::transform(vertexIndex, outerVertex.begin(),
                                       [&](const auto& i) { return ComputeIntersection(outerCentroid, normal, vertex[i], vertex[i]); });

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
                solid->AddFacet(new G4TriangularFacet{innerCentroid,
                                                      innerVertex[0],
                                                      innerVertex[vertexIndex.size() - 1],
                                                      G4FacetVertexType::ABSOLUTE});
                for (auto i{std::ssize(vertexIndex) - 1}; i > 0; --i) {
                    solid->AddFacet(new G4TriangularFacet{innerCentroid,
                                                          innerVertex[i],
                                                          innerVertex[i - 1],
                                                          G4FacetVertexType::ABSOLUTE});
                }
                // side surface
                for (int i{}; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4QuadrangularFacet{innerVertex[i],
                                                            innerVertex[i + 1],
                                                            outerVertex[i + 1],
                                                            outerVertex[i],
                                                            G4FacetVertexType::ABSOLUTE});
                }
                solid->AddFacet(new G4QuadrangularFacet{innerVertex[vertexIndex.size() - 1],
                                                        innerVertex[0],
                                                        outerVertex[0],
                                                        outerVertex[vertexIndex.size() - 1],
                                                        G4FacetVertexType::ABSOLUTE});
                // outer surface
                for (int i{}; i < std::ssize(vertexIndex) - 1; ++i) {
                    solid->AddFacet(new G4TriangularFacet{outerCentroid,
                                                          outerVertex[i],
                                                          outerVertex[i + 1],
                                                          G4FacetVertexType::ABSOLUTE});
                }
                solid->AddFacet(new G4TriangularFacet{outerCentroid,
                                                      outerVertex[vertexIndex.size() - 1],
                                                      outerVertex[0],
                                                      G4FacetVertexType::ABSOLUTE});
                solid->SetSolidClosed(true);
                return solid;
            }};

        // Crystal

        const auto logicCrystal{
            Make<G4LogicalVolume>(
                solidCrystal(fmt::format("{}Crystal_{}", name, moduleID)),
                lyso,
                name + "Crystal")};
        const auto physicalCrystal{
            Make<G4PVPlacement>(
                G4Transform3D{},
                logicCrystal,
                fmt::format("{}Crystal_{}", name, moduleID),
                Mother().LogicalVolume(),
                true,
                moduleID,
                checkOverlaps)};

        /////////////////////////////////////////////
        // Construct Optical Surface
        /////////////////////////////////////////////

        const auto rfSurface{new G4OpticalSurface("reflector", unified, polished, dielectric_metal)};
        new G4LogicalSkinSurface{"airPaintSurface", logicCrystal, rfSurface};
        rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

        const auto airPaintSurface{new G4OpticalSurface("AirPaint", unified, polished, dielectric_metal)};
        new G4LogicalBorderSurface{"airPaintSurface", Mother().PhysicalVolume(), physicalCrystal, airPaintSurface};
        airPaintSurface->SetMaterialPropertiesTable(airPaintSurfacePropertiesTable);

        const auto ecalPMCoupler{FindSibling<ECALPhotoSensor>()};
        if (ecalPMCoupler) {
            const auto couplerSurface{new G4OpticalSurface("coupler", unified, polished, dielectric_dielectric)};
            new G4LogicalBorderSurface{"couplerSurface",
                                       physicalCrystal,
                                       ecalPMCoupler->PhysicalVolume(name + "PMCoupler", moduleID),
                                       couplerSurface};
            couplerSurface->SetMaterialPropertiesTable(couplerSurfacePropertiesTable);
        }

        ++moduleID;
    }
}

} // namespace MACE::Detector::Definition
