#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UserEventAction.hh"

namespace MACE::SimMACE::Action {

class EventAction final : public Utility::NonCopyableBase,
                          public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event*) override;
};

} // namespace MACE::SimMACE::Action
