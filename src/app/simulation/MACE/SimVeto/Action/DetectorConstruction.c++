#include "MACE/Detector/Description/PDSVeto.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/ECALField.h++"
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
    /*reset veto center to 0*/{
        const auto& mmsField{Description::MMSField::Instance()};
        const auto& solenoid{Description::Solenoid::Instance()};
        const auto& ecalField{Description::ECALField::Instance()};
        mmsField.Length(0.);
        solenoid.S1Length(0.);
        solenoid.S2Length(0.);
        solenoid.S3Length(0.);
        solenoid.T1Radius(0.);
        solenoid.T2Radius(0.);
        ecalField.Length(0.);
    }

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
