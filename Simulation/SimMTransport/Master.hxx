#pragma once

#include "Global.hxx"

namespace MACE::Simulation::SimMTransport {

class Master {
private:
    clock_t fBeginCPUTime;
    clock_t fEndCPUTime;
    time_t fRunBeginTime;
    time_t fRunEndTime;

public:
    Master();
    ~Master() noexcept = default;
    Master(const Master&) = delete;
    Master& operator=(const Master&) = delete;

    void Initialize();
    void Run();
    void Finalize();

    [[nodiscard]] clock_t GetUsedCPUTime() const { return fEndCPUTime - fBeginCPUTime; }
    [[nodiscard]] time_t GetRunBeginTime() const { return fRunBeginTime; }
    [[nodiscard]] time_t GetRunEndTime() const { return fRunEndTime; }

private:
    void ProgressReport(size_t jobSend) const;
};

} // namespace MACE::Simulation::SimMTransport
