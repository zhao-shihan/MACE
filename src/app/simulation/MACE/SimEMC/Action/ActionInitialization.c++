#include "MACE/SimEMC/Action/ActionInitialization.h++"
#include "MACE/SimEMC/Action/EventAction.h++"
#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimEMC/Action/RunAction.h++"

namespace MACE::SimEMC::inline Action {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
}

} // namespace MACE::SimEMC::inline Action
