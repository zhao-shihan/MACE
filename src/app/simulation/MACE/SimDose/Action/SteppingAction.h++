#pragma once

#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimDose::inline Action {

class SteppingAction final : public NeutrinoKillerSteppingAction<SteppingAction> {
public:
    SteppingAction();

private:
    auto SteppingActionWithoutNeutrino(const G4Step& step) -> void override;
};

} // namespace MACE::SimDose::inline Action
