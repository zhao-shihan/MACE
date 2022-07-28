#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimMACE::Action {

class ActionInitialization final : public Utility::NonMoveableBase,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::SimMACE::Action
