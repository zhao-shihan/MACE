#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::ActionInitialization final :
    public G4VUserActionInitialization {
public:
    ActionInitialization() = default;
    ~ActionInitialization() noexcept = default;

    void Build() const override;
};
