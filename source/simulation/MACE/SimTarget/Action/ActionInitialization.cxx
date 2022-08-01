#include "MACE/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Action/RunAction.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Action/TrackingAction.hxx"

namespace MACE::SimTarget::Action {

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());
    SetUserAction(new SteppingAction());
    SetUserAction(new TrackingAction());
}

} // namespace MACE::SimTarget::Action
