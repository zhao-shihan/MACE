// #include "MACE/Detector/Description/EMC.h++"
// #include "MACE/Detector/Geometry/Fast/EMC.h++"
// #include "MACE/Env/BasicEnv.h++"
// #include "MACE/Utility/LiteralUnit.h++"
// #include "MACE/Utility/MathConstant.h++"
// #include "MACE/Utility/PhysicalConstant.h++"

// #include "G4IntersectionSolid.hh"
// #include "G4LogicalBorderSurface.hh"
// #include "G4LogicalSkinSurface.hh"
// #include "G4NistManager.hh"
// #include "G4OpticalSurface.hh"
// #include "G4PVPlacement.hh"
// #include "G4QuadrangularFacet.hh"
// #include "G4SystemOfUnits.hh"
// #include "G4TessellatedSolid.hh"
// #include "G4TriangularFacet.hh"
// #include "G4Tubs.hh"
// #include "G4UnionSolid.hh"

// #include <algorithm>
// #include <utility>

// namespace MACE::Detector::Geometry::Fast {

// // using namespace MathConstant;
// using namespace LiteralUnit::Length;
// using namespace LiteralUnit::Time;
// using namespace LiteralUnit::Energy;
// using namespace LiteralUnit::AmountOfSubstance;
// using namespace LiteralUnit::Density;
// using namespace LiteralUnit::Mass;
// using namespace LiteralUnit::Pressure;
// using namespace LiteralUnit::Temperature;
// using namespace MathConstant;
// using namespace PhysicalConstant;

// void EMC::Construct(G4bool checkOverlaps) {

// const auto& description = Description::EMC::Instance();

// const auto name = description.Name();

// const auto innerRadius = description.InnerRadius();
// const auto fCrystalHypotenuse = description.CrystalHypotenuse();

// const auto pmtRadius = description.PMTRadius();
// const auto pmtCouplerThickness = description.PMTCouplerThickness();
// const auto pmtWindowThickness = description.PMTWindowThickness();
// const auto pmtCathodeThickness = description.PMTCathodeThickness();

// const auto couplerEnergyBin = description.CouplerEnergyBin();
// const auto couplerRefractiveIndex = description.CouplerRefractiveIndex();
// const auto pmtWaveLengthBin = description.PMTWaveLengthBin();
// const auto pmtQuantumEfficiency = description.PMTQuantumEfficiency();
// const auto csiEnergyBin = description.CsIEnergyBin();
// const auto csiScintillationComponent1 = description.CsIScintillationComponent1();
// const auto scintillationYield = description.ScintillationYield();
// const auto scintillationTimeConstant1 = description.ScintillationTimeConstant1();
// const auto resolutionScale = description.ResolutionScale();

// /////////////////////////////////////////////
// // Define Element and Material
// /////////////////////////////////////////////

// const auto nistManager = G4NistManager::Instance();
// const auto hydrogenElement = nistManager->FindOrBuildElement("H");
// const auto carbonElement = nistManager->FindOrBuildElement("C");
// const auto oxygenElement = nistManager->FindOrBuildElement("O");
// const auto siliconElement = nistManager->FindOrBuildElement("Si");
// const auto potassiumElement = nistManager->FindOrBuildElement("K");
// const auto bromideElement = nistManager->FindOrBuildElement("Br");
// const auto yttriumElement = nistManager->FindOrBuildElement("Y");
// const auto antimonyElement = nistManager->FindOrBuildElement("Sb");
// const auto iodideElement = nistManager->FindOrBuildElement("I");
// const auto cesiumElement = nistManager->FindOrBuildElement("Cs");
// const auto lanthanumElement = nistManager->FindOrBuildElement("La");
// const auto ceriumElement = nistManager->FindOrBuildElement("Ce");
// const auto lutetiumElement = nistManager->FindOrBuildElement("Lu");
// const auto thaliumElement = nistManager->FindOrBuildElement("Tl");

// const auto galactic = new G4Material("galactic", 1, 1.008_g_mol, 1.e-25_g_cm3, kStateGas, 2.73_K, 3.e-18_Pa);

// const auto siliconeOil = new G4Material("silicone_oil", 0.97_g_cm3, 4, kStateLiquid);
// siliconeOil->AddElement(carbonElement, 2);
// siliconeOil->AddElement(hydrogenElement, 6);
// siliconeOil->AddElement(oxygenElement, 1);
// siliconeOil->AddElement(siliconElement, 1);

// const auto csI = new G4Material("CsI", 4.51_g_cm3, 3, kStateSolid);
// csI->AddElement(cesiumElement, 0.507556);
// csI->AddElement(iodideElement, 0.484639);
// csI->AddElement(thaliumElement, 0.007805);

// const auto bialkali = new G4Material("Bialkali", 2.0_g_cm3, 3, kStateSolid);
// bialkali->AddElement(potassiumElement, 2);
// bialkali->AddElement(cesiumElement, 1);
// bialkali->AddElement(antimonyElement, 1);

// const auto glass = new G4Material("Quartz", 2.64_g_cm3, 2, kStateSolid);
// glass->AddElement(oxygenElement, 0.532570);
// glass->AddElement(siliconElement, 0.467430);

// //////////////////////////////////////////////////
// // Construct Material Optical Properties Tables
// //////////////////////////////////////////////////

// const auto fLambdaMin = 200_nm;
// const auto fLambdaMax = 700_nm;
// std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
//                                      h_Planck * c_light / fLambdaMin};

// // air properties

// auto airPropertiesTable = new G4MaterialPropertiesTable();
// airPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.00, 1.00});
// galactic->SetMaterialPropertiesTable(airPropertiesTable);

// // couple properties

// auto siliconeOilPropertiesTable = new G4MaterialPropertiesTable();
// siliconeOilPropertiesTable->AddProperty("RINDEX", couplerEnergyBin, couplerRefractiveIndex);
// siliconeOilPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {15_cm, 15_cm});
// siliconeOil->SetMaterialPropertiesTable(siliconeOilPropertiesTable);

// // quartz properties

// auto windowPropertiesTable = new G4MaterialPropertiesTable();
// windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.54, 1.54});
// glass->SetMaterialPropertiesTable(windowPropertiesTable);

// // CsI(Tl) properties

// auto csiPropertiesTable = new G4MaterialPropertiesTable;
// csiPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.79, 1.79});
// csiPropertiesTable->AddProperty("GROUPVEL", fEnergyPair, {167.482, 167.482});
// csiPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {370_mm, 370_mm});
// csiPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", csiEnergyBin, csiScintillationComponent1);
// csiPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", scintillationYield);
// csiPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintillationTimeConstant1);
// csiPropertiesTable->AddConstProperty("RESOLUTIONSCALE", resolutionScale);
// csI->SetMaterialPropertiesTable(csiPropertiesTable);
// if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VerboseLevel::Verbose) {
//     csiPropertiesTable->DumpTable();
// }

// // Define Surface properties
// auto rfSurfacePropertiesTable = new G4MaterialPropertiesTable();
// rfSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0.985, 0.985});

// auto rfoilSurfacePropertiesTable = new G4MaterialPropertiesTable();
// rfoilSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {1, 1});

// auto tapeSurfacePropertiesTable = new G4MaterialPropertiesTable();
// tapeSurfacePropertiesTable->AddProperty("TRANSMITTANCE", fEnergyPair, {0, 0});

// std::vector<G4double> cathodeSurfacePropertiesEnergy(pmtWaveLengthBin.size());
// std::vector<G4double> cathodeSurfacePropertiesEfficiency(pmtQuantumEfficiency.size());
// std::transform(pmtWaveLengthBin.begin(), pmtWaveLengthBin.end(), cathodeSurfacePropertiesEnergy.begin(),
//                [](auto val) { return h_Planck * c_light / (val * nm / mm); });
// std::transform(pmtQuantumEfficiency.begin(), pmtQuantumEfficiency.end(), cathodeSurfacePropertiesEfficiency.begin(),
//                [](auto n) { return n * perCent; });

// auto cathodeSurfacePropertiesTable = new G4MaterialPropertiesTable();
// cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
// cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);
// if (Env::BasicEnv::Instance().GetVerboseLevel() >= Env::VerboseLevel::Verbose) {
//     cathodeSurfacePropertiesTable->DumpTable();
// }

// /////////////////////////////////////////////
// // Construct Volumes
// /////////////////////////////////////////////

// const auto& emc = Description::EMC::Instance();
// const auto& vertex = emc.Mesh().fVertex;
// const auto& faceList = emc.Mesh().fFaceList;

// for (G4int copyNo = 0;
//      auto&& [centroid, normal, vertexIndex] : std::as_const(faceList)) { // loop over all EMC face
//     const auto centroidMagnitude = centroid.mag();
//     auto fCrystalLength = fCrystalHypotenuse * centroidMagnitude;

// const auto crytalInnerHypotenuse = innerRadius;
// const auto crytalOuterHypotenuse = crytalInnerHypotenuse + fCrystalHypotenuse;
// const auto outerHypotenuse = crytalOuterHypotenuse;

// const auto crystalOuterRadius = crytalOuterHypotenuse * centroidMagnitude;
// const auto outerRadius = outerHypotenuse * centroidMagnitude;

// // make a crystal-shaped solid with certain shrinkage (e.g. shrink with coat thickness)
// const auto MakeTessellatedSolid =
//     [&,
//      midHypotenuse = (innerRadius + outerHypotenuse) / 2,
//      midCentroid = (innerRadius + outerHypotenuse) / 2 * centroid](const auto& name) {
//         constexpr auto crystalHypotenuseExtension = 1 * cm;
//         const auto crystalLengthExtension = crystalHypotenuseExtension * centroidMagnitude;

// const auto innerHypotenuseHere = innerRadius - crystalHypotenuseExtension;
// const auto innerCentroidHere = innerHypotenuseHere * centroid;
// std::vector<G4ThreeVector> innerVertexHere(vertexIndex.size());
// std::ranges::transform(vertexIndex, innerVertexHere.begin(),
//                        [&](const auto& i) { return innerHypotenuseHere * vertex[i]; });
// const auto outerHypotenuseHere = outerHypotenuse + crystalHypotenuseExtension;
// const auto outerCentroidHere = outerHypotenuseHere * centroid;
// std::vector<G4ThreeVector> outerVertexHere(vertexIndex.size());
// std::ranges::transform(vertexIndex, outerVertexHere.begin(),
//                        [&](const auto& i) { return outerHypotenuseHere * vertex[i]; });

// // clang-format off

// // Pentagon:
// //      0
// //   /  |  \
//                 //  1 - C - 4
// //  \ / \  /
// //   2 - 3
// //
// // Hexagon:
// //     0 - 5
// //   / \  / \
//                 //  1 - C - 4
// //  \ /  \ /
// //   2 - 3

// // clang-format on

// const auto solid = Make<G4TessellatedSolid>(name);
// // inner surface
// solid->AddFacet(new G4TriangularFacet(innerCentroidHere,
//                                       innerVertexHere[0],
//                                       innerVertexHere[vertexIndex.size() - 1],
//                                       G4FacetVertexType::ABSOLUTE));
// for (auto i = vertexIndex.size() - 1; i > 0; --i) {
//     solid->AddFacet(new G4TriangularFacet(innerCentroidHere,
//                                           innerVertexHere[i],
//                                           innerVertexHere[i - 1],
//                                           G4FacetVertexType::ABSOLUTE));
// }
// // side surface
// for (auto i = 0; i < vertexIndex.size() - 1; ++i) {
//     solid->AddFacet(new G4QuadrangularFacet(innerVertexHere[i],
//                                             innerVertexHere[i + 1],
//                                             outerVertexHere[i + 1],
//                                             outerVertexHere[i],
//                                             G4FacetVertexType::ABSOLUTE));
// }
// solid->AddFacet(new G4QuadrangularFacet(innerVertexHere[vertexIndex.size() - 1],
//                                         innerVertexHere[0],
//                                         outerVertexHere[0],
//                                         outerVertexHere[vertexIndex.size() - 1],
//                                         G4FacetVertexType::ABSOLUTE));
// // outer surface
// for (auto i = 0; i < vertexIndex.size() - 1; ++i) {
//     solid->AddFacet(new G4TriangularFacet(outerCentroidHere,
//                                           outerVertexHere[i],
//                                           outerVertexHere[i + 1],
//                                           G4FacetVertexType::ABSOLUTE));
// }
// solid->AddFacet(new G4TriangularFacet(outerCentroidHere,
//                                       outerVertexHere[vertexIndex.size() - 1],
//                                       outerVertexHere[0],
//                                       G4FacetVertexType::ABSOLUTE));
// solid->SetSolidClosed(true);
// return solid;
// };

// const auto Transform =
//     [&normal,
//      crystalOuterCentroid = crystalOuterRadius * centroid / centroidMagnitude,
//      rotation = G4Rotate3D{normal.theta(), CLHEP::HepZHat.cross(normal)}](double offsetInNormalDirection) {
//         return G4Translate3D{crystalOuterCentroid + offsetInNormalDirection * normal} * rotation;
//     };

// // Crystal

// const auto solidCrystal = MakeTessellatedSolid("temp");
// const auto cutCrystalBox = Make<G4Box>("temp", 1 * m, 1 * m, fCrystalLength / 2);
// const auto crystalTransform = Transform(-fCrystalLength / 2);
// const auto cutSoildCrystal = Make<G4IntersectionSolid>("EMCCrystal", solidCrystal, cutCrystalBox, crystalTransform);
// //========================================== CsI(Tl) ============================================
// const auto logicCrystal = Make<G4LogicalVolume>(cutSoildCrystal, csI, "EMCCrystal");
// //===============================================================================================
// const auto physicalCrystal = Make<G4PVPlacement>(G4Transform3D{},
//                                                  logicCrystal,
//                                                  "EMCCrystal",
//                                                  Mother().LogicalVolume().get(),
//                                                  true,
//                                                  copyNo,
//                                                  checkOverlaps);

// // Optical Photon Collection

// const auto solidOptocoupler = Make<G4Tubs>("temp", 0, pmtRadius, pmtCouplerThickness / 2, 0, 2 * pi);
// const auto logicOptocoupler = Make<G4LogicalVolume>(solidOptocoupler, siliconeOil, "EMCOptocoupler");
// const auto optocouplerTransform = Transform(pmtCouplerThickness / 2);
// const auto physicalOptocoupler = Make<G4PVPlacement>(optocouplerTransform,
//                                                      logicOptocoupler,
//                                                      "EMCOptocoupler",
//                                                      Mother().LogicalVolume().get(),
//                                                      true,
//                                                      copyNo,
//                                                      checkOverlaps);

// const auto solidWindow = Make<G4Tubs>("temp", 0, pmtRadius, pmtWindowThickness / 2, 0, 2 * pi);
// const auto logicWindow = Make<G4LogicalVolume>(solidWindow, glass, "EMCWindow");
// const auto windowTransform = Transform(pmtCouplerThickness + pmtWindowThickness / 2);
// const auto physicalWindow = Make<G4PVPlacement>(windowTransform,
//                                                 logicWindow,
//                                                 "EMCWindow",
//                                                 Mother().LogicalVolume().get(),
//                                                 true,
//                                                 copyNo,
//                                                 checkOverlaps);

// const auto solidCathode = Make<G4Tubs>("temp", 0, pmtRadius, pmtCathodeThickness / 2, 0, 2 * pi);
// const auto logicCathode = Make<G4LogicalVolume>(solidCathode, bialkali, "EMCCathode");
// const auto cathodeTransform = Transform(pmtCouplerThickness + pmtWindowThickness + pmtCathodeThickness / 2);
// const auto physicalCathode = Make<G4PVPlacement>(cathodeTransform,
//                                                  logicCathode,
//                                                  "EMCCathode",
//                                                  Mother().LogicalVolume().get(),
//                                                  true,
//                                                  copyNo,
//                                                  checkOverlaps);
// ++copyNo;

// // Add Surface properities

// auto rfSurface = new G4OpticalSurface("reflector", unified, polished, dielectric_metal);
// new G4LogicalSkinSurface("rfSurface", logicCrystal, rfSurface);
// rfSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

// auto rfoilSurface = new G4OpticalSurface("rfoil", unified, polished, dielectric_dielectric);
// new G4LogicalBorderSurface("rfoilSurface", physicalCrystal, physicalOptocoupler, rfoilSurface);
// rfoilSurface->SetMaterialPropertiesTable(rfoilSurfacePropertiesTable);

// auto tapeSurface = new G4OpticalSurface("rfoil", unified, polished, dielectric_metal);
// new G4LogicalBorderSurface("rfoilSurface", Mother().PhysicalVolume().get(), physicalCrystal, tapeSurface);
// tapeSurface->SetMaterialPropertiesTable(tapeSurfacePropertiesTable);

// auto optocouplerSurface = new G4OpticalSurface("Optocoupler", unified, polished, dielectric_metal);
// new G4LogicalBorderSurface("optocouplerSurface", physicalOptocoupler, Mother().PhysicalVolume().get(), optocouplerSurface);
// optocouplerSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

// auto windowSurface = new G4OpticalSurface("Window", unified, polished, dielectric_metal);
// new G4LogicalBorderSurface("windowSurface", physicalWindow, Mother().PhysicalVolume().get(), windowSurface);
// windowSurface->SetMaterialPropertiesTable(rfSurfacePropertiesTable);

// auto cathodeSurface = new G4OpticalSurface("Cathode", glisur, polished, dielectric_metal);
// new G4LogicalSkinSurface("cathodeSkinSurface", logicCathode, cathodeSurface);
// cathodeSurface->SetMaterialPropertiesTable(cathodeSurfacePropertiesTable);
// }
// }

// } // namespace MACE::Detector::Geometry::Fast
