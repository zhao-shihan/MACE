#pragma once

#include "Utility/G4MPIRunManager.hxx"
#include "Utility/ObserverPtr.hxx"
#include "SimMACE/Global.hxx"
#include "SimMACE/Action/DetectorConstruction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Action/EventAction.hxx"

class MACE::SimMACE::RunManager final :
    public MACE::G4MPIRunManager {
public:
    static auto& Instance() { return *static_cast<RunManager*>(GetRunManager()); }

    RunManager();
    ~RunManager() noexcept = default;
    RunManager(const RunManager&) = delete;
    RunManager& operator=(const RunManager&) = delete;

    auto& GetDetectorConstruction()   const { return *static_cast<DetectorConstruction*>(userDetector); }
    auto& GetPhysicsList()            const { return *physicsList; }
    auto& GetRunAction()              const { return *static_cast<RunAction*>(userRunAction); }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetEventAction()            const { return *static_cast<EventAction*>(userEventAction); }
    // auto& GetStackingAction()         const { return *static_cast<*>(userStackingAction); }
    // auto& GetTrackingAction()         const { return *static_cast<*>(userTrackingAction); }
    // auto& GetSteppingAction()         const { return *static_cast<*>(userSteppingAction); }
};
