#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/MPIRunManager.h++"
#include "MACE/Extension/Geant4X/MPIRunMessenger.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.h++"

#include "G4Exception.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "mpi.h"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <string>

namespace MACE::inline Extension::Geant4X {

namespace internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        mpiEnv.AtCommWorldWorker() or
        mpiEnv.GetVerboseLevel() == Env::VerboseLevel::Quiet) {
        static std::streambuf* gG4coutBufExchanger = nullptr;
        gG4coutBufExchanger = G4cout.rdbuf(gG4coutBufExchanger);
    }
}

} // namespace internal

MPIRunManager::MPIRunManager() :
    internal::PreG4RunManagerInitFlipG4cout{},
    G4RunManager{},
    internal::PostG4RunManagerInitFlipG4cout{},
    fNEventToBeMPIProcessed{},
    fEventIDRange{},
    fPrintProgressModulo{Env::MPIEnv::Instance().Sequential() ? 1 : Env::MPIEnv::Instance().CommWorldSize() + 1},
    fEventWallTimeStopwatch{},
    fEventWallTimeStatistic{},
    fRunCPUTimeStopwatch{},
    fRunCPUTime{},
    fRunWallTimeStopwatch{},
    fRunWallTime{},
    fRunBeginSystemTime{},
    fRunEndSystemTime{} {
    MPIRunMessenger::Instance().AssignTo(this);
}

auto MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (nEvent < mpiEnv.CommWorldSize()) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4Exception("MACE::Utility::G4Util::MPIRunManager::CheckNEventIsAtLeastCommSize(...)",
                        "TooFewNEventOrTooMuchRank",
                        JustWarning,
                        "The number of G4Event must be greater or equal to the number of MPI ranks,\n"
                        "otherwise deadlock could raise in execution code.\n"
                        "Please be careful.");
        }
        return;
    }

    MPIUtil::MPIReseedPRNG(*G4Random::getTheEngine());
    fNEventToBeMPIProcessed = nEvent;
    fEventIDRange = MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.CommWorldSize(), mpiEnv.CommWorldRank());
    G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
}

auto MPIRunManager::RunInitialization() -> void {
    // initialize run
    G4RunManager::RunInitialization();
    // wait for everyone to start
    MACE_MPI_CALL_WITH_CHECK(MPI_Barrier,
                             MPI_COMM_WORLD)
    // start the run stopwatch
    fRunBeginSystemTime = std::chrono::system_clock::now();
    fRunCPUTimeStopwatch.Reset();
    fRunWallTimeStopwatch.Reset();
    // report
    if (fPrintProgressModulo >= 0) {
        RunBeginReport(runIDCounter);
    }
}

auto MPIRunManager::InitializeEventLoop(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    // initialize event loop
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
    // reset event time statistic
    fEventWallTimeStatistic = {};
    // restart the event stopwatch just before the first event begins
    fEventWallTimeStopwatch.Reset();
}

auto MPIRunManager::ProcessOneEvent(G4int iEvent) -> void {
    G4RunManager::ProcessOneEvent(fEventIDRange.begin + iEvent * fEventIDRange.step);
}

auto MPIRunManager::TerminateOneEvent() -> void {
    // the terminating event ID
    const auto terminatedEventID = currentEvent->GetEventID();
    // terminate the event
    G4RunManager::TerminateOneEvent();
    // read & restart the event stopwatch
    fEventWallTimeStatistic.Fill(fEventWallTimeStopwatch.SecondsElapsed());
    fEventWallTimeStopwatch.Reset();
    // report
    if (fPrintProgressModulo > 0 and terminatedEventID % fPrintProgressModulo == 0) {
        EventEndReport(terminatedEventID);
    }
}

auto MPIRunManager::RunTermination() -> void {
    // terminate the run
    const auto endedRun = runIDCounter;
    G4RunManager::RunTermination();
    // stop the run stopwatch
    fRunWallTime = fRunWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fRunCPUTimeStopwatch.SecondsUsed();
    // wait for everyone to finish
    MACE_MPI_CALL_WITH_CHECK(MPI_Barrier,
                             MPI_COMM_WORLD)
    // run end report
    if (fPrintProgressModulo >= 0) {
        RunEndReport(endedRun);
    }
}

namespace {

auto FormatSecondToDHMS(double secondsInTotal) -> std::string {
    const auto totalSeconds = std::llround(secondsInTotal);
    const auto div86400 = std2b::div(totalSeconds, 86400ll);
    const auto div3600 = std2b::div(div86400.rem, 3600ll);
    const auto div60 = std2b::div(div3600.rem, 60ll);
    const auto& [day, hour, minute, second] = std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem);
    const auto addDay = day > 0;
    const auto addHour = addDay or hour > 0;
    const auto addMinute = addDay or addHour or minute > 0;

    std::array<char, std::numeric_limits<decltype(totalSeconds)>::digits10 + 3> buffer;
    std::string dhms;
    if (addDay) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), day).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("d ");
    }
    if (addHour) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), hour).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("h ");
    }
    if (addMinute) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), minute).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("m ");
    }
    const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), second).ptr;
    dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("s");
    return dhms;
}

} // namespace

auto MPIRunManager::EventEndReport(const G4int eventID) const -> void {
    using namespace std::string_literals;
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    const auto nEventRemain = numberOfEventToBeProcessed - numberOfEventProcessed;
    const auto eta = FormatSecondToDHMS(nEventRemain * fEventWallTimeStatistic.Mean());
    const auto etaError = numberOfEventProcessed < 5 ?
                              "N/A"s :
                              FormatSecondToDHMS(3 * nEventRemain * std::sqrt(fEventWallTimeStatistic.Variance() / numberOfEventProcessed));
    const auto progress = static_cast<double>(numberOfEventProcessed) / numberOfEventToBeProcessed;
    using scsc = std::chrono::system_clock;
    fmt::print("Rank {} > {:%FT%T%z} > G4Event {} finished \n"
               "  Est. rem. time: {} +/- {}  Rank progress: {}/{} ({:.4}%)\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), eventID,
               eta, etaError, numberOfEventProcessed, numberOfEventToBeProcessed, 100 * progress);
}

auto MPIRunManager::RunEndReport(const G4int runID) const -> void {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    using scsc = std::chrono::system_clock;
    fmt::print("------------------------------> G4Run Finished <------------------------------\n"
               "{:%FT%T%z} > G4Run {} finished on {} ranks\n"
               "  Start time: {:%FT%T%z}\n"
               "   Wall time: {:.2f} seconds{}\n"
               "------------------------------> G4Run Finished <------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize(),
               fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)),
               fRunWallTime, fRunWallTime > 60 ? " (" + FormatSecondToDHMS(fRunWallTime) + ")" : "");
}

auto MPIRunManager::RunBeginReport(const G4int runID) -> void {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    using scsc = std::chrono::system_clock;
    fmt::print("-------------------------------> G4Run Starts <-------------------------------\n"
               "{:%FT%T%z} > G4Run {} starts on {} ranks\n"
               "-------------------------------> G4Run Starts <-------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize());
}

} // namespace MACE::inline Extension::Geant4X
