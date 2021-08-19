#ifndef Master_hh
#define Master_hh 1

#include "Global.hh"

class MACE::SimMuTransport::Master {
private:
    clock_t fBeginCPUTime;
    clock_t fEndCPUTime;
    time_t  fRunBeginTime;
    time_t  fRunEndTime;

public:
    Master();
    ~Master();
    Master(const Master&) = delete;
    Master& operator=(const Master&) = delete;

    void Initialize();
    void Run();
    void Finalize();

    clock_t GetUsedCPUTime() const { return fEndCPUTime - fBeginCPUTime; }
    time_t  GetRunBeginTime() const { return fRunBeginTime; }
    time_t  GetRunEndTime() const { return fRunEndTime; }

private:
    void ProgressReport(size_t jobSend) const;
};

#endif

