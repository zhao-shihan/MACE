#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimMACE::inline Action {

class ActionInitialization final : public NonMoveableBase,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::SimMACE::inline Action
