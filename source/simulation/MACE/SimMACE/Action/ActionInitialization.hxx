#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimMACE::Action {

class ActionInitialization final : public Utility::NonCopyableBase,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::SimMACE::Action
