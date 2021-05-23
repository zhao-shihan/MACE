#include "PSIMACEAnalysisManager.hh"

#include "G4MTRunManager.hh"
#include "G4Run.hh"

#include <iomanip>
#include <numeric>

G4Mutex mutex_PSIMACEAnalysisManager;

PSIMACEAnalysisManager* PSIMACEAnalysisManager::instance = nullptr;

PSIMACEAnalysisManager* PSIMACEAnalysisManager::Instance() {
    mutex_PSIMACEAnalysisManager.lock();
    if (!instance) { instance = new PSIMACEAnalysisManager(); }
    mutex_PSIMACEAnalysisManager.unlock();
    return instance;
}

PSIMACEAnalysisManager::PSIMACEAnalysisManager() :
    fFileName("PSIMACE"),
    fout{ nullptr, nullptr, nullptr } {}

PSIMACEAnalysisManager::~PSIMACEAnalysisManager() {
    for (size_t i = 0; i < 3; ++i) { if (fout[i] != nullptr) { delete fout[i]; } }
}

void PSIMACEAnalysisManager::Open() {
    if (G4ThisThread::get_id() != G4MTRunManager::GetMasterRunManager()->GetMasterThreadId()) { return; }
    G4String fileName[3]{
        fFileName + "_MCP.csv",
        fFileName + "_CsI.csv",
        fFileName + "_MWPC.csv"
    };
    G4String title[3]{
        "t/ns,x/mm,y/mm",
        "t/ns,E/MeV",
        "t/ns,x/mm,y/mm,z/mm,chamberNb"
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

G4Mutex mutex_PSIMACEAnalysisManager_MCP;

void PSIMACEAnalysisManager::WriteMCPHitList(std::vector<std::array<G4double, 3>>& hitList) {
    //
    // write MCP hits.
    //
    mutex_PSIMACEAnalysisManager_MCP.lock();
    if (!hitList.empty()) {
        auto& data = hitList.back();
        *fout[fMCP] << data[0] << ',' << data[1] << ',' << data[2];
        hitList.pop_back();
        while (!hitList.empty()) {
            data = hitList.back();
            *fout[fMCP] << '\n' << data[0] << ',' << data[1] << ',' << data[2];
            hitList.pop_back();
        }
        *fout[fMCP] << std::endl;
    }
    mutex_PSIMACEAnalysisManager_MCP.unlock();
}

G4Mutex mutex_PSIMACEAnalysisManager_CsI;

void PSIMACEAnalysisManager::WriteCsIHitList(std::vector<std::array<G4double, 2>>& hitList) {
    //
    // write CsI hits.
    //
    mutex_PSIMACEAnalysisManager_CsI.lock();
    if (!hitList.empty()) {
        auto& data = hitList.back();
        *fout[fCsI] << data[0] << ',' << data[1];
        hitList.pop_back();
        while (!hitList.empty()) {
            data = hitList.back();
            *fout[fCsI] << '\n' << data[0] << ',' << data[1];
            hitList.pop_back();
        }
        *fout[fCsI] << std::endl;
    }
    mutex_PSIMACEAnalysisManager_CsI.unlock();
}

G4Mutex mutex_PSIMACEAnalysisManager_MWPC;

void PSIMACEAnalysisManager::WriteMWPCHitList(std::vector<std::pair<std::array<G4double, 4>, G4int>>& hitList) {
    //
    // write MagSpec hits.
    //
    mutex_PSIMACEAnalysisManager_MWPC.lock();
    if (!hitList.empty()) {
        auto& data = hitList.back().first;
        auto& chamberNb = hitList.back().second;
        *fout[fMWPC] <<
            data[0] << ',' << data[1] << ',' << data[2] << ',' << data[3] << ',' << chamberNb;
        hitList.pop_back();
        while (!hitList.empty()) {
            data = hitList.back().first;
            chamberNb = hitList.back().second;
            *fout[fMWPC] << '\n' <<
                data[0] << ',' << data[1] << ',' << data[2] << ',' << data[3] << ',' << chamberNb;
            hitList.pop_back();
        }
        *fout[fMWPC] << std::endl;
    }
    mutex_PSIMACEAnalysisManager_MWPC.unlock();
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