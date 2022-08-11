#pragma once

#include "MACE/Utility/DivideIndices.hxx"

#include "G4RunManager.hh"

#include <chrono>
#include <ctime>

namespace MACE::Geant4X {

namespace Internal {

class FlipG4cout {
protected:
    FlipG4cout();
};

class PreG4RunManagerInitFlipG4cout : private FlipG4cout {};

class PostG4RunManagerInitFlipG4cout : private FlipG4cout {};

} // namespace Internal

class MPIRunManager : private Internal::PreG4RunManagerInitFlipG4cout,
                      public G4RunManager,
                      private Internal::PostG4RunManagerInitFlipG4cout {
public:
    MPIRunManager();
    virtual ~MPIRunManager() = default;
    MPIRunManager(const MPIRunManager&) = delete;
    MPIRunManager& operator=(const MPIRunManager&) = delete;

    static auto GetRunManager() { return static_cast<MPIRunManager*>(G4RunManager::GetRunManager()); }

    const auto& GetTotalNumberOfEventToBeProcessed() const { return fTotalNumberOfEventsToBeProcessed; }
    const auto& GetPrintProgress() const { return fPrintProgress; }

    void SetPrintProgress(G4int val);

    virtual void BeamOn(G4int nEvent, const char* macroFile = nullptr, G4int nSelect = -1) override;
    virtual void RunInitialization() override;
    virtual void InitializeEventLoop(G4int nEvent, const char* macroFile = nullptr, G4int nSelect = -1) override;
    virtual void ProcessOneEvent(G4int) override;
    virtual void TerminateOneEvent() override;
    virtual void RunTermination() override;

private:
    G4bool CheckNEventIsAtLeastCommSize(G4int nEvent) const;
    void RunBeginReport() const;
    void EventEndReport() const;
    void RunEndReport() const;

private:
    G4int fTotalNumberOfEventsToBeProcessed;
    Utility::IntegralIndexRange<G4int> fEventIDRange;
    G4int fEventIDCounter;

    G4int fPrintProgress;
    std::chrono::system_clock::time_point fRunBeginSystemTime;
    std::chrono::steady_clock::time_point fRunBeginWallTime;
    clock_t fRunBeginCPUTime;
    std::chrono::steady_clock::time_point fEventBeginWallTime;
    std::chrono::duration<G4double> fEventWallTime;
    G4double fNAvgEventWallTime;
    G4double fNDevEventWallTime;
    std::chrono::duration<G4double> fRunWallTime;
    clock_t fRunCPUTime;
};

} // namespace MACE::Geant4X
