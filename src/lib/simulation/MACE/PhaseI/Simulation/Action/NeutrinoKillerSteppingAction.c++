#include "MACE/PhaseI/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::PhaseI::inline Simulation::inline Action {

NeutrinoKillerSteppingAction<void>::NeutrinoKillerSteppingAction() :
    NeutrinoKillerSteppingAction<NeutrinoKillerSteppingAction<void>>{this} {}

} // namespace MACE::PhaseI::inline Simulation::inline Action
