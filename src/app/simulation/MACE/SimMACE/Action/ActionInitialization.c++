#include "MACE/SimMACE/Action/ActionInitialization.h++"
#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Action/RunAction.h++"

namespace MACE::SimMACE {

void ActionInitialization::Build() const {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
}

} // namespace MACE::SimMACE
