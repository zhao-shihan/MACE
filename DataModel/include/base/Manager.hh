#pragma once

#include "DataModelGlobal.hh"

class MACE::DataModel::Base::Manager {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(Manager);
protected:
    Manager();
    ~Manager();

public:
    void Open(const char* fileName);
    void WriteAndClose(Int_t writeOption = 0, Int_t writeBufSize = 0, Option_t* closeOption = nullptr, Bool_t branchStatus = true);

    template<class StringType>
    void SetBranchTitle(const StringType& title) { fTitle = title; }

    // template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
    // TBranch* CreateBranchFromPersistencyList(const std::vector<PersistencyType*>* persistencyList);
    // template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
    // TBranch* CreateBranchFromPersistencyList(const std::vector<PersistencyType*>& persistencyList);
    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
    TBranch* Persistify(const std::vector<TransientType*>* transientList);
    template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
    TBranch* Persistify(const std::vector<TransientType*>& transientList);

private:
    TFile* fFile;

protected:
    TString fTitle;
    std::array<TTree*, detectorNum> fTrees;
};

// template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
// TBranch* MACE::DataModel::Base::Manager::CreateBranchFromPersistencyList(const std::vector<PersistencyType*>* persistencyList) {
//     if (persistencyList->empty()) { return nullptr; }
//     TTree* const tree = std::get<kDetector>(fTrees);
//     TBranch* const branch = tree->Branch(fTitle, persistencyList->front(), PersistencyType::LeafList);
//     for (PersistencyType* persistency : *persistencyList) {
//         tree->Fill();
//         branch->SetAddress(persistency);
//     }
//     tree->Fill();
//     branch->ResetAddress();
//     branch->SetStatus(false);
//     return branch;
// }

// template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType>
// TBranch* MACE::DataModel::Base::Manager::CreateBranchFromPersistencyList(const std::vector<PersistencyType*>& persistencyList) {
//     return CreateBranchFromPersistencyList<kDetector, PersistencyType>(&persistencyList);
// }

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
TBranch* MACE::DataModel::Base::Manager::Persistify(const std::vector<TransientType*>* transientList) {
    if (transientList->empty()) { return nullptr; }
    TTree* const tree = std::get<kDetector>(fTrees);
    PersistencyType persistency = transientList->front()->ToPersistency();
    TBranch* const branch = tree->Branch(fTitle, &persistency, PersistencyType::LeafList);
    for (TransientType* transient : *transientList) {
        tree->Fill();
        persistency = transient->ToPersistency();
    }
    tree->Fill();
    branch->ResetAddress();
    branch->SetStatus(false);
    return branch;
}

template<MACE::DataModel::DetectorSubscript kDetector, class PersistencyType, class TransientType>
TBranch* MACE::DataModel::Base::Manager::Persistify(const std::vector<TransientType*>& transientList) {
    return Persistify<kDetector, PersistencyType, TransientType>(&transientList);
}