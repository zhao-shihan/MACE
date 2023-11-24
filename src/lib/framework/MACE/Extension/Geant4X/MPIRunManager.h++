#pragma once

#include "MACE/Math/Statistic.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
#include "MACE/Utility/DivideIndices.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

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

    static auto GetRunManager() -> auto { return static_cast<MPIRunManager*>(G4RunManager::GetRunManager()); }

    auto NEventToBeMPIProcessed() const -> const auto& { return fNEventToBeMPIProcessed; }
    auto PrintProgressModulo() const -> const auto& { return fPrintProgressModulo; }

    auto PrintProgressModulo(const G4int val) -> void { (fPrintProgressModulo = val, printModulo = -1); }

    virtual auto BeamOn(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) -> void override;
    virtual auto RunInitialization() -> void override;
    virtual auto InitializeEventLoop(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) -> void override;
    virtual auto ProcessOneEvent(G4int iEvent) -> void override;
    virtual auto TerminateOneEvent() -> void override;
    virtual auto RunTermination() -> void override;

private:
    auto EventEndReport(const G4int eventID) const -> void;
    auto RunEndReport(const G4int runID) const -> void;

    static auto RunBeginReport(const G4int runID) -> void;

private:
    G4int fNEventToBeMPIProcessed;
    IntegralIndexRange<G4int> fEventIDRange;

    G4int fPrintProgressModulo;
    WallTimeStopwatch<> fEventWallTimeStopwatch;
    Math::Statistic<1> fEventWallTimeStatistic;
    CPUTimeStopwatch<> fRunCPUTimeStopwatch;
    double fRunCPUTime;
    WallTimeStopwatch<> fRunWallTimeStopwatch;
    double fRunWallTime;
    std::chrono::system_clock::time_point fRunBeginSystemTime;
    std::chrono::system_clock::time_point fRunEndSystemTime;
};

} // namespace MACE::inline Extension::Geant4X
