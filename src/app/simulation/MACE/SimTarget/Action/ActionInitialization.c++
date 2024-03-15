#include "MACE/SimTarget/Action/ActionInitialization.h++"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Action/RunAction.h++"
#include "MACE/SimTarget/Action/SteppingAction.h++"
#include "MACE/SimTarget/Action/TrackingAction.h++"

namespace MACE::SimTarget::inline Action {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new SteppingAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new RunAction);
}

} // namespace MACE::SimTarget::inline Action
