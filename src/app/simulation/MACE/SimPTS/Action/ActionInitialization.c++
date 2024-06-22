#include "MACE/SimPTS/Action/ActionInitialization.h++"
#include "MACE/SimPTS/Action/EventAction.h++"
#include "MACE/SimPTS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimPTS/Action/RunAction.h++"
#include "MACE/SimPTS/Action/TrackingAction.h++"

namespace MACE::SimPTS {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
}

} // namespace MACE::SimPTS
