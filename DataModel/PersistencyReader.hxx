#pragma once

#include <memory>

#include "DataModel/Global.hxx"
#include "DataModel/Interface/PersistencyHandler.hxx"

class MACE::DataModel::PersistencyReader :
    public MACE::DataModel::Interface::PersistencyHandler {
    PersistencyReader(const PersistencyReader&) = delete;
    PersistencyReader& operator=(const PersistencyReader&) = delete;
public:
    PersistencyReader();
    virtual ~PersistencyReader() {}

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "READ"); }
    virtual void Close(Option_t* option = nullptr) { PersistencyHandler::Close(option); }

    template<class Data_t>
    TTree* GetTree(Long64_t i) { return fFile->Get<TTree>(GetTreeName<Data_t>(i)); }
    template<class DataInTree_t, class DataInList_t = DataInTree_t>
    std::pair<std::vector<std::shared_ptr<DataInList_t>>, TTree*> CreateListFromTree(Long64_t treeIndex = 0);
};

template<class DataInTree_t, class DataInList_t>
std::pair<std::vector<std::shared_ptr<DataInList_t>>, TTree*> MACE::DataModel::PersistencyReader::CreateListFromTree(Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<DataInList_t, DataInTree_t>,
        "DataInList_t should be the base of DataInTree_t");
    std::vector<std::shared_ptr<DataInList_t>> dataList(0);
    TTree* tree = GetTree<DataInTree_t>(treeIndex);
    if (tree != nullptr) {
        dataList.reserve(tree->GetEntries());
        DataInList_t::ReadBranches(tree);
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);
            dataList.emplace_back(std::make_shared<DataInList_t>());
        }
    }
    return std::make_pair(dataList, tree);
}