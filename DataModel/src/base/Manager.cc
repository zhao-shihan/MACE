#include "base/Manager.hh"

using namespace MACE::DataModel::Base;

Manager::Manager() :
    fFile(nullptr),
    fTitle("Event"),
    fTrees{ nullptr } {}

Manager::~Manager() {
    Close();
}

void Manager::Open(const char* fileName) {
    if (fFile != nullptr) {
        if (fFile->IsOpen()) {
            std::cerr << "From MACE::DataModel::Base::Manager::Open : Current file <" << fFile->GetName() << "> not closed." << std::endl;
            return;
        }
        delete fFile;
    }
    fFile = new TFile(fileName, "RECREATE");
    for (uint32_t i = 0; i < detectorNum; ++i) {
        fTrees[i] = new TTree(detectorName[i], detectorName[i]);
    }
}

void Manager::Write() {
    if (fFile == nullptr) { return; }
    if (fFile->IsOpen()) {
        for (auto tree : fTrees) {
            tree->Write();
        }
    }
}

void Manager::Close() {
    if (fFile == nullptr) { return; }
    if (fFile->IsOpen()) {
        fFile->Close();
    }
    delete fFile;
    fFile = nullptr;
}