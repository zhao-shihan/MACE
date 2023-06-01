#include "MACE/SimMACE/Action/ActionInitialization.h++"
#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Action/RunAction.h++"

using MACE::SimMACE::ActionInitialization;

void ActionInitialization::Build() const {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
}
