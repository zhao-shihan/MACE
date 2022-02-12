#pragma once

#include <memory>

#include "DataModel/Global.hxx"
#include "DataModel/Interface/PersistencyHandler.hxx"

class MACE::DataModel::PersistencyWriter :
    public MACE::DataModel::Interface::PersistencyHandler {
    PersistencyWriter(const PersistencyWriter&) = delete;
    PersistencyWriter& operator=(const PersistencyWriter&) = delete;
public:
    enum TreeOperation {
        kJustWrite,
        kDeleteAfterWrite
    };

public:
    PersistencyWriter();
    virtual ~PersistencyWriter();

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "RECREATE"); }
    virtual void Close(Option_t* option = nullptr) override;

    template<class DataInTree_t, class DataInList_t>
    TTree* CreateTreeFromList(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex = 0, TreeOperation behaviour = kDeleteAfterWrite);
    template<class DataInTree_t, class DataInList_t>
    TTree* CreateTreeFromList(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex = 0, TreeOperation behaviour = kDeleteAfterWrite);
    template<class DataInTree_t, class DataInList_t>
    TTree* CreateTreeFromList(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex = 0, TreeOperation behaviour = kDeleteAfterWrite);
    template<class DataInTree_t, class DataInList_t>
    TTree* CreateTreeFromList(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex = 0, TreeOperation behaviour = kDeleteAfterWrite);

    void AppendTree(TTree* tree, TreeOperation behaviour = kJustWrite) { fTreeAndBehaviours.emplace_back(tree, behaviour); }

    void WriteTrees(Int_t option = 0, Int_t bufsize = 0);

private:
    template<class DataInTree_t, class DataInList_t, class PointerOfDataInTree_t>
    TTree* CreateTreeFromList(const std::vector<PointerOfDataInTree_t>& dataList, Long64_t treeIndex, TreeOperation behaviour = kDeleteAfterWrite);

private:
    std::vector<std::pair<TTree*, TreeOperation>> fTreeAndBehaviours;
};

template<class DataInTree_t, class DataInList_t>
TTree* MACE::DataModel::PersistencyWriter::
CreateTreeFromList(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex, TreeOperation behaviour) {
    return CreateTreeFromList<DataInTree_t, DataInList_t, DataInList_t*>(dataList, treeIndex, behaviour);
}

template<class DataInTree_t, class DataInList_t>
TTree* MACE::DataModel::PersistencyWriter::
CreateTreeFromList(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex, TreeOperation behaviour) {
    return CreateTreeFromList<DataInTree_t, DataInList_t, const DataInList_t*>(dataList, treeIndex, behaviour);
}

template<class DataInTree_t, class DataInList_t>
TTree* MACE::DataModel::PersistencyWriter::
CreateTreeFromList(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex, TreeOperation behaviour) {
    return CreateTreeFromList<DataInTree_t, DataInList_t, std::shared_ptr<DataInList_t>>(dataList, treeIndex, behaviour);
}

template<class DataInTree_t, class DataInList_t>
TTree* MACE::DataModel::PersistencyWriter::
CreateTreeFromList(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex, TreeOperation behaviour) {
    return CreateTreeFromList<DataInTree_t, DataInList_t, std::shared_ptr<const DataInList_t>>(dataList, treeIndex, behaviour);
}

template<class DataInTree_t, class DataInList_t, class PointerOfDataInTree_t>
TTree* MACE::DataModel::PersistencyWriter::
CreateTreeFromList(const std::vector<PointerOfDataInTree_t>& dataList, Long64_t treeIndex, TreeOperation behaviour) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<DataInTree_t, DataInList_t>,
        "DataInList_t should be derived from DataInTree_t");
    TString name = PersistencyHandler::GetTreeName<DataInTree_t>(treeIndex);
    TTree* tree = new TTree(name, name);
    DataInTree_t::CreateBranches(tree);
    for (auto&& data : dataList) {
        data->FillBranches();
        tree->Fill();
    }
    fTreeAndBehaviours.emplace_back(tree, behaviour);
    return tree;
}