#pragma once

#include "MACE/Math/Statistic.h++"
#include "MACE/Utility/CPUTimeStopwatch.h++"
#include "MACE/Utility/DivideIndices.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/WallTimeStopwatch.h++"

#include "G4RunManager.hh"

#include "mpi.h"

#include "gsl/gsl"

#include <chrono>

namespace MACE::inline Extension::Geant4X {

namespace internal {

class FlipG4cout {
protected:
    FlipG4cout();
};

class PreG4RunManagerInitFlipG4cout : private FlipG4cout {};

class PostG4RunManagerInitFlipG4cout : private FlipG4cout {};

} // namespace internal

class MPIRunManager : public NonMoveableBase,
                      private internal::PreG4RunManagerInitFlipG4cout,
                      public G4RunManager,
                      private internal::PostG4RunManagerInitFlipG4cout {
public:
    MPIRunManager();
    virtual ~MPIRunManager() = default;

    static auto GetRunManager() -> auto { return static_cast<MPIRunManager*>(G4RunManager::GetRunManager()); }

    auto PrintProgressModulo() const -> const auto& { return fPrintProgressModulo; }
    auto EventWallTimeStatistic() const -> const auto& { return fEventWallTimeStatistic; }

    auto PrintProgressModulo(G4int val) -> void { fPrintProgressModulo = val, printModulo = -1; }

    virtual auto BeamOn(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) -> void override;
    virtual auto ConfirmBeamOnCondition() -> G4bool override;
    virtual auto RunInitialization() -> void override;
    virtual auto InitializeEventLoop(G4int nEvent, gsl::czstring macroFile = nullptr, G4int nSelect = -1) -> void override;
    virtual auto ProcessOneEvent(G4int iEvent) -> void override;
    virtual auto TerminateOneEvent() -> void override;
    virtual auto RunTermination() -> void override;

private:
    using scsc = std::chrono::system_clock;

    auto EventEndReport(G4int eventID) const -> void;

    static auto RunBeginReport(G4int runID) -> void;
    static auto PerRankRunEndReport(G4int runID, double wallTime, double cpuTime) -> void;
    static auto RunEndReport(G4int runID, scsc::time_point runBeginTime, double maxWallTime, double totalCPUTime) -> void;

    static auto SToDHMS(double secondsInTotal) -> std::string;

private:
    G4int fPrintProgressModulo;

    IntegralIndexRange<G4int> fRunPlanOfThisRank;

    WallTimeStopwatch<> fEventWallTimeStopwatch;
    Math::Statistic<1> fEventWallTimeStatistic;

    scsc::time_point fRunBeginSystemTime;
    WallTimeStopwatch<> fRunWallTimeStopwatch;
    CPUTimeStopwatch<> fRunCPUTimeStopwatch;

    MPI_Request fRunBeginBarrierRequest;
    MPI_Request fRunEndBarrierRequest;
};

} // namespace MACE::inline Extension::Geant4X
