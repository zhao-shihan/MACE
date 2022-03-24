#pragma once

#include "Global.hxx"
#include "Track.hxx"

namespace MACE::Simulation::SimMTransport {

class Worker {
private:
    Track* const fTrack;
    clock_t fBeginCPUTime;
    clock_t fEndCPUTime;

public:
    Worker();
    ~Worker();
    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

    void Initialize();
    void Run();
    void Finalize();

    [[nodiscard]] clock_t GetUsedCPUTime() const { return fEndCPUTime - fBeginCPUTime; }
};

} // namespace MACE::Simulation::SimMTransport
