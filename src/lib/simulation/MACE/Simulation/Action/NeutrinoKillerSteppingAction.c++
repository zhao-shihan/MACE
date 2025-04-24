#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::inline Simulation::inline Action {

NeutrinoKillerSteppingAction<void>::NeutrinoKillerSteppingAction() :
    NeutrinoKillerSteppingAction<NeutrinoKillerSteppingAction<void>>{this} {}

} // namespace MACE::inline Simulation::inline Action
