#pragma once

#include "G4UserRunAction.hh"

namespace MACE::Simulation::SimTarget::Action {

class RunAction final : public G4UserRunAction {
public:
    RunAction() = default;
    ~RunAction() noexcept = default;
    RunAction(const RunAction&) = delete;
    RunAction& operator=(const RunAction&) = delete;

    void EndOfRunAction(const G4Run*) override;
};

} // namespace MACE::Simulation::SimTarget::Action
