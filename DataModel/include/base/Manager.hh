#pragma once

#include "TTree.h"
#include "TFile.h"

#include "DataModelGlobal.hh"

class MACE::DataModel::Base::Manager {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(Manager);
protected:
    Manager();
    ~Manager();

public:
    void Open(const char* fileName);
    void Write();
    void Close();

    template<class StringType>
    void SetBranchTitle(const StringType& title) { fTitle = title; }

    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
    TBranch* CreateBranchFromPersistencyList(const std::vector<PersistencyType*>* persistencyList);
    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
    TBranch* CreateBranchFromPersistencyList(const std::vector<PersistencyType*>& persistencyList);
    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
    TBranch* CreateBranchFromTransientList(const std::vector<TransientType*>* transientList);
    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
    TBranch* CreateBranchFromTransientList(const std::vector<TransientType*>& transientList);

private:
    TFile* fFile;

protected:
    TString fTitle;
    std::array<TTree*, detectorNum> fTrees;
};

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
TBranch* MACE::DataModel::Base::Manager::CreateBranchFromPersistencyList(const std::vector<PersistencyType*>* persistencyList) {
    if (persistencyList->empty()) { return nullptr; }
    TTree* const tree = std::get<kDetector>(fTrees);
    TBranch* const branch = tree->Branch(fTitle, persistencyList->front(), PersistencyType::LeafList);
    for (PersistencyType* persistency : *persistencyList) {
        branch->Fill();
        branch->SetAddress(persistency);
    }
    branch->Fill();
    branch->ResetAddress();
    return branch;
}

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
TBranch* MACE::DataModel::Base::Manager::CreateBranchFromPersistencyList(const std::vector<PersistencyType*>& persistencyList) {
    return CreateBranchFromPersistencyList<kDetector, PersistencyType>(&persistencyList);
}

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
TBranch* MACE::DataModel::Base::Manager::CreateBranchFromTransientList(const std::vector<TransientType*>* transientList) {
    if (transientList->empty()) { return nullptr; }
    TTree* const tree = std::get<kDetector>(fTrees);
    PersistencyType persistency = transientList->front()->ToPersistency();
    TBranch* const branch = tree->Branch(fTitle, &persistency, PersistencyType::LeafList);
    for (TransientType* transient : *transientList) {
        branch->Fill();
        persistency = transient->ToPersistency();
    }
    branch->Fill();
    branch->ResetAddress();
    return branch;
}

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
TBranch* MACE::DataModel::Base::Manager::CreateBranchFromTransientList(const std::vector<TransientType*>& transientList) {
    return CreateBranchFromTransientList<kDetector, PersistencyType, TransientType>(&transientList);
}