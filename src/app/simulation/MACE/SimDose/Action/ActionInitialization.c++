#include "MACE/SimDose/Action/ActionInitialization.h++"
#include "MACE/SimDose/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimDose/Action/RunAction.h++"
#include "MACE/SimDose/Action/SteppingAction.h++"

namespace MACE::SimDose {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new SteppingAction);
}

} // namespace MACE::SimDose
