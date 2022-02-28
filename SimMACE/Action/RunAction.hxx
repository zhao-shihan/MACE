#pragma once

#include "G4UserRunAction.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::RunAction final :
    public G4UserRunAction {
    friend RunManager;
private:
    RunAction() = default;
    ~RunAction() noexcept = default;

public:
    RunAction(const RunAction&) = delete;
    RunAction& operator=(const RunAction&) = delete;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};
