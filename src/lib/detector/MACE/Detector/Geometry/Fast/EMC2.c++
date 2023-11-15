#include "MACE/Detector/Description/EMC2.h++"
#include "MACE/Detector/Geometry/Fast/EMC2.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4TessellatedSolid.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

#include <utility>

namespace MACE::Detector::Geometry::Fast {

// using namespace MathConstant;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::Time;
using namespace LiteralUnit::Energy;
using namespace LiteralUnit::AmountOfSubstance;
using namespace LiteralUnit::Density;
using namespace LiteralUnit::Mass;
using namespace LiteralUnit::Pressure;
using namespace LiteralUnit::Temperature;
using namespace PhysicalConstant;

void EMC::Construct(G4bool checkOverlaps) {

    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();
    const auto innerRadius = description.InnerRadius();
    const auto crystalLength = description.CrystalLength();
    const auto pmtRadius = description.PMTRadius();
    const auto pmtCouplerThickness = description.PMTCouplerThickness();
    const auto pmtWindowThickness = description.PMTWindowThickness();
    const auto pmtCathodeThickness = description.PMTCathodeThickness();

    const auto couplerEnergyBin = description.CouplerEnergyBin();
    const auto couplerRefractiveIndex = description.CouplerRefractiveIndex();
    const auto pmtWaveLengthBin = description.PMTWaveLengthBin();
    const auto pmtQuantumEfficiency = description.PMTQuantumEfficiency();
    const auto csiEnergyBin = description.CsIEnergyBin();
    const auto csiScintillationComponent1 = description.CsIScintillationComponent1();
    const auto scintillationYield = description.ScintillationYield();
    const auto scintillationTimeConstant1 = description.ScintillationTimeConstant1();
    const auto resolutionScale = description.ResolutionScale();

    /////////////////////////////////////////////
    // Define Material
    /////////////////////////////////////////////

    const auto nistManager = G4NistManager::Instance();
    const auto hydrogenElement = nistManager->FindOrBuildElement("H");
    const auto carbonElement = nistManager->FindOrBuildElement("C");
    const auto oxygenElement = nistManager->FindOrBuildElement("O");
    const auto siliconElement = nistManager->FindOrBuildElement("Si");
    const auto potassiumElement = nistManager->FindOrBuildElement("K");
    const auto bromideElement = nistManager->FindOrBuildElement("Br");
    const auto yttriumElement = nistManager->FindOrBuildElement("Y");
    const auto antimonyElement = nistManager->FindOrBuildElement("Sb");
    const auto iodideElement = nistManager->FindOrBuildElement("I");
    const auto cesiumElement = nistManager->FindOrBuildElement("Cs");
    const auto lanthanumElement = nistManager->FindOrBuildElement("La");
    const auto ceriumElement = nistManager->FindOrBuildElement("Ce");
    const auto lutetiumElement = nistManager->FindOrBuildElement("Lu");
    const auto thaliumElement = nistManager->FindOrBuildElement("Tl");

    const auto galactic = new G4Material("galactic", 1, 1.008_g_mol, 1.e-25_g_cm3, kStateGas, 2.73_K, 3.e-18_Pa);

    const auto siliconeOil = new G4Material("silicone_oil", 0.97_g_cm3, 4, kStateLiquid);
    siliconeOil->AddElement(carbonElement, 2);
    siliconeOil->AddElement(hydrogenElement, 6);
    siliconeOil->AddElement(oxygenElement, 1);
    siliconeOil->AddElement(siliconElement, 1);

    const auto csI = new G4Material("CsI", 4.51_g_cm3, 3, kStateSolid);
    csI->AddElement(cesiumElement, 0.507556);
    csI->AddElement(iodideElement, 0.484639);
    csI->AddElement(thaliumElement, 0.007805);

    const auto bialkali = new G4Material("Bialkali", 2.0_g_cm3, 3, kStateSolid);
    bialkali->AddElement(potassiumElement, 2);
    bialkali->AddElement(cesiumElement, 1);
    bialkali->AddElement(antimonyElement, 1);

    const auto glass = new G4Material("Quartz", 2.64_g_cm3, 2, kStateSolid);
    glass->AddElement(oxygenElement, 0.532570);
    glass->AddElement(siliconElement, 0.467430);

    /////////////////////////////////////////////
    // Construct Material Properties Tables
    /////////////////////////////////////////////

    const auto fLambdaMin = 200_nm;
    const auto fLambdaMax = 700_nm;
    std::vector<G4double> fEnergyPair = {h_Planck * c_light / fLambdaMax,
                                         h_Planck * c_light / fLambdaMin};

    // air

    auto airPropertiesTable = new G4MaterialPropertiesTable();
    airPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.00, 1.00});
    galactic->SetMaterialPropertiesTable(airPropertiesTable);

    // couple

    auto siliconeOilPropertiesTable = new G4MaterialPropertiesTable();
    siliconeOilPropertiesTable->AddProperty("RINDEX", couplerEnergyBin, couplerRefractiveIndex);
    siliconeOilPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {15_cm, 15_cm});
    siliconeOil->SetMaterialPropertiesTable(siliconeOilPropertiesTable);

    // quartz

    auto windowPropertiesTable = new G4MaterialPropertiesTable();
    windowPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.54, 1.54});
    glass->SetMaterialPropertiesTable(windowPropertiesTable);

    // PMT QE

    std::vector<G4double> cathodeSurfacePropertiesEnergy(pmtWaveLengthBin.size());
    std::vector<G4double> cathodeSurfacePropertiesEfficiency(pmtQuantumEfficiency.size());
    std::transform(pmtWaveLengthBin.begin(), pmtWaveLengthBin.end(), cathodeSurfacePropertiesEnergy.begin(),
                   [](auto val) { return h_Planck * c_light / (val * nm / mm); });
    std::transform(pmtQuantumEfficiency.begin(), pmtQuantumEfficiency.end(), cathodeSurfacePropertiesEfficiency.begin(),
                   [](auto n) { return n * perCent; });

    auto cathodeSurfacePropertiesTable = new G4MaterialPropertiesTable();
    cathodeSurfacePropertiesTable->AddProperty("REFLECTIVITY", fEnergyPair, {0., 0.});
    cathodeSurfacePropertiesTable->AddProperty("EFFICIENCY", cathodeSurfacePropertiesEnergy, cathodeSurfacePropertiesEfficiency);

    // CsI(Tl)

    auto csiPropertiesTable = new G4MaterialPropertiesTable;
    csiPropertiesTable->AddProperty("RINDEX", fEnergyPair, {1.79, 1.79});
    csiPropertiesTable->AddProperty("GROUPVEL", fEnergyPair, {167.482, 167.482});
    csiPropertiesTable->AddProperty("ABSLENGTH", fEnergyPair, {370_mm, 370_mm});
    csiPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", csiEnergyBin, csiScintillationComponent1);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", scintillationYield);
    csiPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintillationTimeConstant1);
    csiPropertiesTable->AddConstProperty("RESOLUTIONSCALE", resolutionScale);
    csI->SetMaterialPropertiesTable(csiPropertiesTable);

    /////////////////////////////////////////////
    // Construct Volumes
    /////////////////////////////////////////////
}

} // namespace MACE::Detector::Geometry::Fast
