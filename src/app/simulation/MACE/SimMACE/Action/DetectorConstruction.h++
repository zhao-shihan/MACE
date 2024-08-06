#pragma once

#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Detector/Description/Vacuum.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Simulation/Messenger/NumericMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include "muc/tuple"

#include <memory>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE::SimMACE::inline Action {

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
        Detector::Assembly::MMS::DescriptionInUse,
        std::tuple<Detector::Description::Accelerator,
                   Detector::Description::BeamDegrader,
                   Detector::Description::BeamMonitor,
                   Detector::Description::EMC,
                   Detector::Description::EMCField,
                   Detector::Description::EMCMagnet,
                   Detector::Description::EMCShield,
                   Detector::Description::Filter,
                   Detector::Description::MCP,
                   Detector::Description::MCPChamber,
                   Detector::Description::ShieldingWall,
                   Detector::Description::Solenoid,
                   Detector::Description::Target,
                   Detector::Description::Vacuum,
                   Detector::Description::World>>>;

private:
    G4bool fCheckOverlap;

    double fMinDriverStep;
    double fDeltaChord;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    NumericMessenger<DetectorConstruction>::Register<DetectorConstruction> fNumericMessengerRegister;
};

} // namespace MACE::SimMACE::inline Action
