#include "MACE/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/SimTarget/Action/EventAction.hxx"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Action/RunAction.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Action/TrackingAction.hxx"

namespace MACE::SimTarget::Action {

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new SteppingAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new EventAction);
    SetUserAction(new RunAction);
}

} // namespace MACE::SimTarget::Action
