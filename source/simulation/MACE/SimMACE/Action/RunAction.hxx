#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

#include "G4UserRunAction.hh"

namespace MACE::SimMACE::Action {

class RunAction final : public Utility::NonCopyableBase,
                        public G4UserRunAction {
public:
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};

} // namespace MACE::SimMACE::Action
