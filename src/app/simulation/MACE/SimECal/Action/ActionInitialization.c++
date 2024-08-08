#include "MACE/SimECal/Action/ActionInitialization.h++"
#include "MACE/SimECal/Action/EventAction.h++"
#include "MACE/SimECal/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimECal/Action/RunAction.h++"
#include "MACE/SimECal/Action/TrackingAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimECal::inline Action {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace MACE::SimECal::inline Action
