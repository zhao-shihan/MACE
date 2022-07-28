#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimTarget::Action {

class ActionInitialization final : public Utility::NonMoveableBase,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::SimTarget::Action
