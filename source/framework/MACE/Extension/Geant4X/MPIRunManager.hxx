#pragma once

#include "MACE/Utility/CPUTimer.hxx"
#include "MACE/Utility/DivideIndices.hxx"
#include "MACE/Utility/WallTimer.hxx"

#include "G4RunManager.hh"

#include "gsl/gsl"

#include <chrono>
#include <ctime>
#include <string_view>

namespace MACE::inline Extension::Geant4X {

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

    const auto& TotalNumberOfEventToBeProcessed() const { return fTotalNumberOfEventsToBeProcessed; }
    const auto& PrintProgressModulo() const { return fPrintProgressModulo; }

    void PrintProgressModulo(G4int val);

    virtual void BeamOn(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) override;
    virtual void RunInitialization() override;
    virtual void InitializeEventLoop(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) override;
    virtual void ProcessOneEvent(G4int iEvent) override;
    virtual void TerminateOneEvent() override;
    virtual void RunTermination() override;

private:
    void EventEndReport(G4int eventID) const;
    void RunEndReport(G4int runID) const;

    static void RunBeginReport(G4int runID);
    static std::string FormatSecondToDHMS(long secondsInTotal);

private:
    G4int fTotalNumberOfEventsToBeProcessed;
    IntegralIndexRange<G4int> fEventIDRange;

    G4int fPrintProgressModulo;
    WallTimer<> fEventWallTimer;
    double fEventWallTime;
    double fNAvgEventWallTime;
    double fNDevEventWallTime;
    CPUTimer<> fRunCPUTimer;
    double fRunCPUTime;
    WallTimer<> fRunWallTimer;
    double fRunWallTime;
    std::chrono::system_clock::time_point fRunBeginSystemTime;
    std::chrono::system_clock::time_point fRunEndSystemTime;
};

} // namespace MACE::inline Extension::Geant4X
