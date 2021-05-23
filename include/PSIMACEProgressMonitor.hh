#ifndef PSIMACE_PROGRESS_MANAGER
#define PSIMACE_PROGRESS_MANAGER 1

#include <ctime>
#include "globals.hh"
#include "G4MTRunManager.hh"

// Class for computing time management and estimation.
//
class PSIMACEProgressMonitor {
public:
    static PSIMACEProgressMonitor* Instance();
private:
    PSIMACEProgressMonitor();
    ~PSIMACEProgressMonitor() {}
    PSIMACEProgressMonitor(const PSIMACEProgressMonitor&) = delete;
    PSIMACEProgressMonitor& operator=(const PSIMACEProgressMonitor&) = delete;

private:
    const G4MTRunManager* fRunManager;

    time_t  fRunStartTime;
    time_t  fRunEndTime;
    G4bool  fTimerStarted;
    G4int   fTotalEventsInThisRun;
    G4int   fTotalEvents;
    G4int   fProcessedEventsInThisRun;
    G4int   fEventsPerReport;
    clock_t fCPUTime;

public:
    void SetNumberOfEventsPerReport(G4int n);
    void SetTotalEvents(G4int n);

    void RunStart();
    void EventComplete();
    void RunComplete();
};

#endif

