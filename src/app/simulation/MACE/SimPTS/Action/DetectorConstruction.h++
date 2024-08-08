#pragma once

#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/ECalField.h++"
#include "MACE/Detector/Description/ECalMagnet.h++"
#include "MACE/Detector/Description/ECalShield.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorA.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorB.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorC.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorD.h++"
#include "MACE/Simulation/Messenger/NumericMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include "muc/tuple"

#include <memory>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE::SimPTS::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto MinDriverStep(double val) -> void { fMinDriverStep = val; }
    auto DeltaChord(double val) -> void { fDeltaChord = val; }

    auto Construct() -> G4VPhysicalVolume* override;

public:
    using DescriptionInUse = muc::tuple_unique_t<muc::tuple_concat_t<
        std::tuple<Detector::Description::VirtualDetectorA,
                   Detector::Description::VirtualDetectorB,
                   Detector::Description::VirtualDetectorC,
                   Detector::Description::VirtualDetectorD,
                   MACE::Detector::Description::Accelerator,
                   MACE::Detector::Description::ECalField,
                   MACE::Detector::Description::ECalMagnet,
                   MACE::Detector::Description::ECalShield,
                   MACE::Detector::Description::FieldOption,
                   MACE::Detector::Description::Filter,
                   MACE::Detector::Description::MCPChamber,
                   MACE::Detector::Description::MMSBeamPipe,
                   MACE::Detector::Description::MMSField,
                   MACE::Detector::Description::MMSMagnet,
                   MACE::Detector::Description::MMSShield,
                   MACE::Detector::Description::ShieldingWall,
                   MACE::Detector::Description::Solenoid,
                   MACE::Detector::Description::World>>>;

private:
    G4bool fCheckOverlap;

    double fMinDriverStep;
    double fDeltaChord;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    NumericMessenger<DetectorConstruction>::Register<DetectorConstruction> fNumericMessengerRegister;
};

} // namespace MACE::SimPTS::inline Action
