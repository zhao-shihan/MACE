#include "MACE/SimMACE/Action/ActionInitialization.h++"
#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Action/RunAction.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimMACE {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace MACE::SimMACE
