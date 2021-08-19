#ifndef Worker_hh
#define Worker_hh 1

#include "Global.hh"
#include "Track.hh"

class MACE::SimMuTransport::Worker {
private:
    Track* const fTrack;
    clock_t          fBeginCPUTime;
    clock_t          fEndCPUTime;

public:
    Worker();
    ~Worker();
    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;
    
    void Initialize();
    void Run();
    void Finalize();

    clock_t GetUsedCPUTime() const { return fEndCPUTime - fBeginCPUTime; }
};

#endif

