#pragma once

#include "MACE/Utility/CPUTimer.hxx"
#include "MACE/Utility/DivideIndices.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "G4RunManager.hh"

#include <chrono>
#include <ctime>
#include <string_view>

namespace MACE::Geant4X {

namespace internal {

class FlipG4cout {
protected:
    FlipG4cout();
};

class PreG4RunManagerInitFlipG4cout : private FlipG4cout {};

class PostG4RunManagerInitFlipG4cout : private FlipG4cout {};

} // namespace internal

class MPIRunManager : private internal::PreG4RunManagerInitFlipG4cout,
                      public G4RunManager,
                      private internal::PostG4RunManagerInitFlipG4cout {
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
    void EventEndReport(G4int event) const;
    void RunEndReport(G4int run) const;

    static void RunBeginReport(G4int run);
    static std::string FormatSecondToDHMS(long secondsInTotal);

private:
    G4int fTotalNumberOfEventsToBeProcessed;
    Utility::IntegralIndexRange<G4int> fEventIDRange;
    G4int fEventIDCounter;

    G4int fPrintProgress;
    Utility::WallTimer<double> fEventWallTimer;
    double fEventWallTime;
    double fNAvgEventWallTime;
    double fNDevEventWallTime;
    Utility::CPUTimer<double> fRunCPUTimer;
    double fRunCPUTime;
    Utility::WallTimer<double> fRunWallTimer;
    double fRunWallTime;
    std::chrono::system_clock::time_point fRunBeginSystemTime;
    std::chrono::system_clock::time_point fRunEndSystemTime;
};

} // namespace MACE::Geant4X
