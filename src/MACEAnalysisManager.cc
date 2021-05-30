#include "MACEAnalysisManager.hh"

#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <sstream>
#include <numeric>

G4ThreadLocal MACEAnalysisManager MACEAnalysisManager::fInstance;

G4String MACEAnalysisManager::fFileName = "MACE";
std::ofstream* MACEAnalysisManager::fout[3] = { nullptr, nullptr, nullptr };
size_t MACEAnalysisManager::fSignalSN = 0;

MACEAnalysisManager::MACEAnalysisManager() :
    fpMCPHitList(nullptr),
    fpCsIHitList(nullptr),
    fpMWPCHitList(nullptr) {}

MACEAnalysisManager::~MACEAnalysisManager() {
    for (size_t i = 0; i < 3; ++i) { if (fout[i] != nullptr) { delete fout[i]; } }
}

void MACEAnalysisManager::Open() {
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
    const G4String fileName[3]{
        fFileName + "_MCP.csv",
        fFileName + "_CsI.csv",
        fFileName + "_MWPC.csv"
    };
    const G4String title[3]{
        "SN,t/ns,x/mm,y/mm",
        "SN,t/ns,E/MeV",
        "SN,t/ns,x/mm,y/mm,z/mm,chamberNb"
    };

    bool isContinue = true;
    for (size_t i = 0; i < 3; ++i) {
        std::ifstream fin(fileName[i]);
        if (fin.is_open()) {
            std::string line;
            if (std::getline(fin, line).eof()) {
                isContinue = false;
                fin.close();
                break;
            }
            fin.close();
        } else {
            isContinue = false;
            break;
        }
    }

    fSignalSN = 0;
    if (isContinue) {
        std::ifstream fin(fileName[fMCP]);
        if (fin.is_open()) {
            fin.seekg(-2, std::ios_base::end);
            char ch;
            do {
                fin.get(ch);
                fin.seekg(-2, std::ios_base::cur);
                if (fin.fail()) { break; }
            } while (ch != '\n');
            fin.seekg(2, std::ios_base::cur);
            fin >> fSignalSN;
            ++fSignalSN;
            fin.close();
        }
    }

    for (size_t i = 0; i < 3; ++i) {
        if (isContinue) {
            fout[i] = new std::ofstream(fileName[i], std::ios::app);
        } else {
            fout[i] = new std::ofstream(fileName[i]);
            *fout[i] << title[i] << std::endl;
        }
        *fout[i] << std::setprecision(std::numeric_limits<G4double>::digits10);
    }
}

G4Mutex mutex_MACEAnalysisManager;

void MACEAnalysisManager::AnalysisAndWrite() {
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
            G4ThreadLocal static std::list<const MACECsIHit*> coincidentCsIHitList;
            G4ThreadLocal static std::list<const MACEMWPCHit*> coincidentMWPCHitList;

            for (auto CsIHit = CsIHitBegin; CsIHit != CsIHitEnd; ++CsIHit) {
                coincidentCsIHitList.push_back(&*CsIHit);
            }
            for (auto MWPCHit = MWPCHitBegin; MWPCHit != MWPCHitEnd; ++MWPCHit) {
                coincidentMWPCHitList.push_back(&*MWPCHit);
            }

            mutex_MACEAnalysisManager.lock();
            WriteCoincidentMCPHit(MCPHit);
            WriteCoincidentCsIHit(coincidentCsIHitList);
            WriteCoincidentMWPCHit(coincidentMWPCHitList);
            ++fSignalSN;
            mutex_MACEAnalysisManager.unlock();

            coincidentCsIHitList.clear();
            coincidentMWPCHitList.clear();
        }
    }
}

void MACEAnalysisManager::WriteCoincidentMCPHit(const MACEMCPHit& MCPHit) const {
    //
    // write MCP signal hit.
    //
    *fout[fMCP] << fSignalSN << ',' << MCPHit.t << ',' << MCPHit.x << ',' << MCPHit.y << std::endl;
}

void MACEAnalysisManager::WriteCoincidentCsIHit(std::list<const MACECsIHit*>& CCsIHitList) const {
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

void MACEAnalysisManager::WriteCoincidentMWPCHit(std::list<const MACEMWPCHit*>& CMWPCHitList) const {
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

void MACEAnalysisManager::Close() {
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
    for (size_t i = 0; i < 3; ++i) {
        if (fout[i] != nullptr) {
            fout[i]->close();
            delete fout[i];
            fout[i] = nullptr;
        }
    }
}