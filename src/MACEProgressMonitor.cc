#include "G4Run.hh"
#include "G4MTRunManager.hh"

#include "MACEProgressMonitor.hh"

MACEProgressMonitor MACEProgressMonitor::fInstance;

MACEProgressMonitor::MACEProgressMonitor() :
    fRunStartTime(0),
    fRunEndTime(0),
    fTimerStarted(false),
    fTotalEventsInThisRun(0),
    fTotalEvents(0),
    fProcessedEventsInThisRun(0),
    fEventsPerReport(1),
    fCPUTime(0) {}

void MACEProgressMonitor::SetNumberOfEventsPerReport(G4int n) {
    if (fTimerStarted) { return; }
    fEventsPerReport = n;
}

void MACEProgressMonitor::SetTotalEvents(G4int n) {
    if (fTimerStarted) { return; }
    fTotalEvents = n;
}

void MACEProgressMonitor::RunStart() {
    if (fTimerStarted) { return; }
    time(&fRunStartTime);
    fTotalEventsInThisRun = G4MTRunManager::GetMasterRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    if (fTotalEvents < fTotalEventsInThisRun) { fTotalEvents = fTotalEventsInThisRun; }
    fProcessedEventsInThisRun = 0;
    fCPUTime = clock();
    fTimerStarted = true;
}

G4Mutex mutex_MACEProgressMonitor;

void MACEProgressMonitor::EventComplete() {
    if (!fTimerStarted) { return; }
    mutex_MACEProgressMonitor.lock();
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
    mutex_MACEProgressMonitor.unlock();
}

void MACEProgressMonitor::RunComplete() {
    if (!fTimerStarted) { return; }
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
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

