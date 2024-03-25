#include "MACE/SimMMS/Action/ActionInitialization.h++"
#include "MACE/SimMMS/Action/EventAction.h++"
#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMMS/Action/RunAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"

namespace MACE::SimMMS {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
}

} // namespace MACE::SimMMS
