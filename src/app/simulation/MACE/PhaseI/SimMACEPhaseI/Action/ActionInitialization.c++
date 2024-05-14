#include "MACE/PhaseI/SimMACEPhaseI/Action/ActionInitialization.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/EventAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/RunAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
