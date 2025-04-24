#include "MACE/Detector/Definition/PDSVeto.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/PDSVeto.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/SimVeto/Action/DetectorConstruction.h++"
#include "MACE/SimVeto/Messenger/DetectorMessenger.h++"
#include "MACE/SimVeto/SD/VetoPMSD.h++"
#include "MACE/SimVeto/SD/VetoSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"

#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimVeto::inline Action {

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{this},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Definition;
    using namespace MACE::Detector::Description;
    /*reset veto center to 0*/ {
        auto& mmsField{MACE::Detector::Description::MMSField::Instance()};
        auto& solenoid{MACE::Detector::Description::Solenoid::Instance()};
        auto& ecalField{MACE::Detector::Description::ECALField::Instance()};
        mmsField.Length(0.);
        solenoid.S1Length(0.);
        solenoid.S2Length(0.);
        solenoid.S3Length(0.);
        solenoid.T1Radius(0.);
        solenoid.T2Radius(0.);
        ecalField.Length(0.);
    }

    fWorld = std::make_unique<MACE::Detector::Definition::World>();
    auto& pdsVeto{fWorld->NewDaughter<MACE::Detector::Definition::PDSVeto>(fCheckOverlap)};

    const auto& vetoName{MACE::Detector::Description::PDSVeto::Instance().Name()};
    const auto& vetoPMSD{new SD::VetoPMSD{vetoName + "PM"}};
    const auto& vetoStripSD{
        new SD::VetoSD{vetoName + "Strip", vetoPMSD}
    };
    for (int categoryID{0}; categoryID < 4; categoryID++) {
        pdsVeto.RegisterSD(fmt::format("VetoStrip_{}", categoryID), vetoStripSD);
    }
    pdsVeto.RegisterSD("VetoCathode", vetoPMSD);

    return fWorld->PhysicalVolume();
}
} // namespace MACE::SimVeto::inline Action
