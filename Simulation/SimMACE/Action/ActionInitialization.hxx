#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::ActionInitialization final :
    public G4VUserActionInitialization {
    friend RunManager;

private:
    ActionInitialization() = default;
    ~ActionInitialization() noexcept = default;
    ActionInitialization(const ActionInitialization&) = delete;
    ActionInitialization& operator=(const ActionInitialization&) = delete;

public:
    void Build() const override;
};
