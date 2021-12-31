#pragma once

#include "Global.hxx"
#include "Master.hxx"
#include "Worker.hxx"

namespace MACE {
    namespace SimMTransport {
        enum RunStatus {
            kRunUndefined,
            kRunInitialized,
            kRunRunning,
            kRunStopped,
            kRunFinalized
        };
    }
}

class MACE::SimMTransport::RunManager {
public:
    static RunManager* Instance();
    ~RunManager();
private:
    static RunManager* fInstance;
    RunManager();
    RunManager(const RunManager&) = delete;
    RunManager& operator=(const RunManager&) = delete;

private:
    Master* fMaster;
    Worker* fWorker;
    RunStatus fStatus;

public:
    void Initialize(int& argc, char**& argv);
    void Run();
    void Finalize();

private:
    void InitialReport() const;
    void FinalReport() const;
};
