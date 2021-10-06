#include "base/Manager.hh"

using namespace MACE::DataModel::Base;

Manager::Manager() :
    fFile(nullptr),
    fTitle("Event"),
    fTrees{ nullptr } {}

Manager::~Manager() {
    WriteAndClose();
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

void Manager::WriteAndClose(Int_t writeOption, Int_t writeBufSize, Option_t* closeOption, Bool_t branchStatus) {
    if (fFile == nullptr) { return; }
    if (fFile->IsOpen()) {
        for (auto tree : fTrees) {
            tree->SetBranchStatus("*");
            tree->Write(nullptr, writeOption, writeBufSize);
        }
        fFile->Close(closeOption);
    }
    delete fFile;
    fFile = nullptr;
}