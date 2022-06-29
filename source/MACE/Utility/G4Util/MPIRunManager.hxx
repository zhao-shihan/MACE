#pragma once

#include "MACE/Utility/DivideIndices.hxx"

#include "G4RunManager.hh"

#include <chrono>
#include <ctime>

namespace MACE::Utility::G4Util {

namespace Detail {

/// @attention This should only be firstly privately inherited by MPIRunManager. It's not intended to be used elsewhere.
class MPIRunManagerInitializeHelper {
protected:
    MPIRunManagerInitializeHelper();
    void PrintStartupMessage();

private:
    static void FlipG4cout();
};

} // namespace Detail

class MPIRunManager : private Detail::MPIRunManagerInitializeHelper,
                      public G4RunManager {
public:
    MPIRunManager();
    virtual ~MPIRunManager() noexcept = default;
    MPIRunManager(const MPIRunManager&) = delete;
    MPIRunManager& operator=(const MPIRunManager&) = delete;

    static auto GetRunManager() { return static_cast<MPIRunManager*>(G4RunManager::GetRunManager()); }

    const auto& GetCommRank() const { return fCommRank; }
    const auto& GetCommSize() const { return fCommSize; }
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
    const int fCommRank;
    const int fCommSize;

    G4int fTotalNumberOfEventsToBeProcessed;
    DividedIndexRange<G4int> fEventIDRange;
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

} // namespace MACE::Utility::G4Util
