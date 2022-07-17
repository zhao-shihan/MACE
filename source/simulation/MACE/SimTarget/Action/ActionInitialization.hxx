#pragma once

#include "G4VUserActionInitialization.hh"

namespace MACE::SimTarget::Action {

class ActionInitialization final : public G4VUserActionInitialization {
public:
    ActionInitialization() = default;
    ~ActionInitialization() noexcept = default;
    ActionInitialization(const ActionInitialization&) = delete;
    ActionInitialization& operator=(const ActionInitialization&) = delete;

    void Build() const override;
};

} // namespace MACE::SimTarget::Action
