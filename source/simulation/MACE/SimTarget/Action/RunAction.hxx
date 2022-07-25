#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

#include "G4UserRunAction.hh"

namespace MACE::SimTarget::Action {

class RunAction final : public Utility::NonCopyableBase,
                        public G4UserRunAction {
public:
    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run*) override;
};

} // namespace MACE::SimTarget::Action
