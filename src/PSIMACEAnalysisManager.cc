#include "PSIMACEAnalysisManager.hh"

#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <iomanip>
#include <numeric>

G4ThreadLocal PSIMACEAnalysisManager PSIMACEAnalysisManager::fInstance;

G4String PSIMACEAnalysisManager::fFileName = "MACE";
std::ofstream* PSIMACEAnalysisManager::fout[3] = { nullptr, nullptr, nullptr };
size_t PSIMACEAnalysisManager::fSignalSN = 0;

PSIMACEAnalysisManager::PSIMACEAnalysisManager() :
    fpMCPHitList(nullptr),
    fpCsIHitList(nullptr),
    fpMWPCHitList(nullptr) {}

PSIMACEAnalysisManager::~PSIMACEAnalysisManager() {
    for (size_t i = 0; i < 3; ++i) { if (fout[i] != nullptr) { delete fout[i]; } }
}

void PSIMACEAnalysisManager::Open() {
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
    fSignalSN = 0;
    G4String fileName[3]{
        fFileName + "_MCP.csv",
        fFileName + "_CsI.csv",
        fFileName + "_MWPC.csv"
    };
    G4String title[3]{
        "SN,t/ns,x/mm,y/mm",
        "SN,t/ns,E/MeV",
        "SN,t/ns,x/mm,y/mm,z/mm,chamberNb"
    };
    for (size_t i = 0; i < 3; ++i) {
        bool isContinue = false;
        std::ifstream fin(fileName[i]);
        if (fin.is_open()) {
            std::string line;
            isContinue = !std::getline(fin, line).eof();
            fin.close();
        }
        if (isContinue) {
            fout[i] = new std::ofstream(fileName[i], std::ios::app);
        } else {
            fout[i] = new std::ofstream(fileName[i]);
            *fout[i] << title[i] << std::endl;
        }
        *fout[i] << std::setprecision(std::numeric_limits<G4double>::digits10);
    }
}

G4Mutex mutex_PSIMACEAnalysisManager;

void PSIMACEAnalysisManager::AnalysisAndWrite() {
    if (fpMCPHitList->empty() || fpMWPCHitList->empty()) { return; }

    G4ThreadLocal static auto compareHit = [&](auto lhs, auto rhs)->bool { return lhs.t < rhs.t; };
    std::sort(fpMCPHitList->begin(), fpMCPHitList->end(), compareHit);
    std::sort(fpCsIHitList->begin(), fpCsIHitList->end(), compareHit);
    std::sort(fpMWPCHitList->begin(), fpMWPCHitList->end(), compareHit);

    auto CsIHitBegin = fpCsIHitList->begin();
    auto CsIHitEnd = CsIHitBegin;
    auto MWPCHitBegin = fpMWPCHitList->begin();
    auto MWPCHitEnd = MWPCHitBegin;

    for (const auto& MCPHit : *fpMCPHitList) {
        G4double CsIWindowBegin = MCPHit.t;
        G4double CsIWindowEnd = CsIWindowBegin + 1. * ns;
        while (CsIHitBegin != fpCsIHitList->end()) {
            if (CsIHitBegin->t < CsIWindowBegin) { ++CsIHitBegin; } else { break; }
        }
        while (CsIHitEnd != fpCsIHitList->end()) {
            if (CsIHitEnd->t < CsIWindowEnd) { ++CsIHitEnd; } else { break; }
        }

        G4double MWPCWindowBegin = MCPHit.t - 60. * ns - 10. * ns;
        G4double MWPCWindowEnd = MWPCWindowBegin + 2. * ns + 10. * ns;
        while (MWPCHitBegin != fpMWPCHitList->end()) {
            if (MWPCHitBegin->t < MWPCWindowBegin) { ++MWPCHitBegin; } else { break; }
        }
        while (MWPCHitEnd != fpMWPCHitList->end()) {
            if (MWPCHitEnd->t < MWPCWindowEnd) { ++MWPCHitEnd; } else { break; }
        }

        if (MWPCHitBegin != MWPCHitEnd) {
            G4ThreadLocal static std::list<const PSIMACECsIHit*> coincidentCsIHitList;
            G4ThreadLocal static std::list<const PSIMACEMWPCHit*> coincidentMWPCHitList;

            for (auto CsIHit = CsIHitBegin; CsIHit != CsIHitEnd; ++CsIHit) {
                coincidentCsIHitList.push_back(&*CsIHit);
            }
            for (auto MWPCHit = MWPCHitBegin; MWPCHit != MWPCHitEnd; ++MWPCHit) {
                coincidentMWPCHitList.push_back(&*MWPCHit);
            }

            mutex_PSIMACEAnalysisManager.lock();
            WriteCoincidentMCPHit(MCPHit);
            WriteCoincidentCsIHit(coincidentCsIHitList);
            WriteCoincidentMWPCHit(coincidentMWPCHitList);
            ++fSignalSN;
            mutex_PSIMACEAnalysisManager.unlock();

            coincidentCsIHitList.clear();
            coincidentMWPCHitList.clear();
        }
    }
}

void PSIMACEAnalysisManager::WriteCoincidentMCPHit(const PSIMACEMCPHit& MCPHit) const {
    //
    // write MCP signal hit.
    //
    *fout[fMCP] << fSignalSN << ',' << MCPHit.t << ',' << MCPHit.x << ',' << MCPHit.y << std::endl;
}

void PSIMACEAnalysisManager::WriteCoincidentCsIHit(std::list<const PSIMACECsIHit*>& CCsIHitList) const {
    //
    // write coincident CsI hits.
    //
    if (!CCsIHitList.empty()) {
        const auto& firstHit = CCsIHitList.front();
        *fout[fCsI] << fSignalSN << ',' << firstHit->t << ',' << firstHit->E;
        CCsIHitList.pop_front();
        for (const auto& hit : CCsIHitList) {
            *fout[fCsI] << '\n' << fSignalSN << ',' << hit->t << ',' << hit->E;
        }
        *fout[fCsI] << std::endl;
    }
}

void PSIMACEAnalysisManager::WriteCoincidentMWPCHit(std::list<const PSIMACEMWPCHit*>& CMWPCHitList) const {
    //
    // write coincident MWPC hits.
    //
    if (!CMWPCHitList.empty()) {
        const auto& firstHit = CMWPCHitList.front();
        *fout[fMWPC] << fSignalSN << ',' << firstHit->t << ','
            << firstHit->x << ',' << firstHit->y << ',' << firstHit->z << ',' << firstHit->chamberNb;
        CMWPCHitList.pop_front();
        for (const auto& hit : CMWPCHitList) {
            *fout[fMWPC] << '\n' << fSignalSN << ','
                << hit->t << ',' << hit->x << ',' << hit->y << ',' << hit->z << ',' << hit->chamberNb;
        }
        *fout[fMWPC] << std::endl;
    }
}

void PSIMACEAnalysisManager::Close() {
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
    for (size_t i = 0; i < 3; ++i) {
        if (fout[i] != nullptr) {
            fout[i]->close();
            delete fout[i];
            fout[i] = nullptr;
        }
    }
}