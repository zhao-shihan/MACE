#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/SimVeto/SD/VetoPMSD.h++"
#include "MACE/SimVeto/SD/VetoStripSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"

#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimVeto::inline Action {

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Definition;
    
    fWorld = std::make_unique<World>();
    auto& pdsVeto{fWorld->NewDaughter<PDSVeto>(fCheckOverlap)};

    const auto& vetoName{MACE::Detector::Description::PDSVeto::Instance().Name()};
    std::cout << "vetoName: " << vetoName << "\n";
    const auto& vetoPMSD{new SD::VetoPMSD{vetoName + "PM"}};
    const auto& vetoStripSD{new SD::VetoStripSD{vetoName + "Strip", vetoPMSD}};
    pdsVeto.RegisterSD("VetoCathode", vetoPMSD);
    for(int typeID{0};typeID<4;typeID++){
        pdsVeto.RegisterSD(fmt::format("VetoStrip_{}", typeID), vetoStripSD);
    }
    
    return fWorld->PhysicalVolume();

    
}
} // namespace MACE::SimVeto::inline Action
