#include "G4Run.hh"
#include "G4MTRunManager.hh"

#include "PSIMACEProgressMonitor.hh"

PSIMACEProgressMonitor* PSIMACEProgressMonitor::Instance() {
    static PSIMACEProgressMonitor instance;
    return &instance;
}

PSIMACEProgressMonitor::PSIMACEProgressMonitor() :
    fRunManager(G4MTRunManager::GetMasterRunManager()),
    fRunStartTime(0),
    fRunEndTime(0),
    fTimerStarted(false),
    fTotalEventsInThisRun(0),
    fTotalEvents(0),
    fProcessedEventsInThisRun(0),
    fEventsPerReport(1000),
    fCPUTime(0) {}

void PSIMACEProgressMonitor::SetNumberOfEventsPerReport(G4int n) {
    fEventsPerReport = n;
}

void PSIMACEProgressMonitor::SetTotalEvents(G4int n) {
    if (fTimerStarted) { return; }
    fTotalEvents = n;
}

void PSIMACEProgressMonitor::RunStart() {
    if (fTimerStarted) { return; }
    time(&fRunStartTime);
    fTotalEventsInThisRun = fRunManager->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    if (fTotalEvents < fTotalEventsInThisRun) { fTotalEvents = fTotalEventsInThisRun; }
    fProcessedEventsInThisRun = 0;
    fCPUTime = clock();
    fTimerStarted = true;
}

G4Mutex mutex_PSIMACEProgressMonitor;

void PSIMACEProgressMonitor::EventComplete() {
    if (!fTimerStarted) { return; }
    mutex_PSIMACEProgressMonitor.lock();
    ++fProcessedEventsInThisRun;
    if (fProcessedEventsInThisRun % fEventsPerReport == 0) {
        time_t currentTime = time(nullptr);
        G4int estTimeRemain = (fTotalEventsInThisRun - fProcessedEventsInThisRun)
            * float(currentTime - fRunStartTime) / fProcessedEventsInThisRun;
        G4int estTimeRemainHr = estTimeRemain / 3600;
        G4int estTimeRemainMin = (estTimeRemain - estTimeRemainHr * 3600) / 60;
        G4int estTimeRemainSec = estTimeRemain - (estTimeRemainMin * 60 + estTimeRemainHr * 3600);
        std::cout
            << ctime(&currentTime)
            << fProcessedEventsInThisRun << '/' << fTotalEvents << " events processed ("
            << 100.f * float(fProcessedEventsInThisRun) / fTotalEvents << "%). "
            << "ETA: " << estTimeRemainHr << "h " << estTimeRemainMin << "m " << estTimeRemainSec << 's'
            << std::endl;
    }
    mutex_PSIMACEProgressMonitor.unlock();
}

void PSIMACEProgressMonitor::RunComplete() {
    if (!fTimerStarted) { return; }
    auto run = G4MTRunManager::GetMasterRunManager()->GetCurrentRun();
    if (run->GetNumberOfEvent() == run->GetNumberOfEventToBeProcessed()) {
        time(&fRunEndTime);
        fCPUTime = clock() - fCPUTime;
        fTimerStarted = false;
        std::cout
            << '\n'
            << "  Start time: " << ctime(&fRunStartTime)
            << "    End time: " << ctime(&fRunEndTime)
            << "Elapsed time: " << difftime(fRunEndTime, fRunStartTime) << "s\n"
            << "    CPU time: " << fCPUTime / CLOCKS_PER_SEC << 's'
            << std::endl;
    }
}

