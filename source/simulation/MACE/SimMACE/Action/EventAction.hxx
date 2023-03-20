#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4UserEventAction.hh"

namespace MACE::SimMACE::inline Action {

class EventAction final : public NonMoveableBase,
                          public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event*) override;
};

} // namespace MACE::SimMACE::inline Action
