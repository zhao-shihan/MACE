#pragma once

#include "G4UserRunAction.hh"

namespace MACE::SimTarget::Action {

class RunAction final : public G4UserRunAction {
public:
    RunAction() = default;
    ~RunAction() noexcept = default;
    RunAction(const RunAction&) = delete;
    RunAction& operator=(const RunAction&) = delete;

    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run*) override;
};

} // namespace MACE::SimTarget::Action
