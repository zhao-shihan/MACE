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
    PersistencyReader(const char* fileName);
    virtual ~PersistencyReader() {}

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "READ"); }
    virtual void Close(Option_t* option = nullptr) { PersistencyHandler::Close(option); }

    template<class Data_t>
    std::vector<std::shared_ptr<Data_t>> CreateListFromTree();
    template<class Data_t>
    TTree* GetTree() { return fFile->Get<TTree>(GetTreeName<Data_t>()); }
};

template<class Data_t>
std::vector<std::shared_ptr<Data_t>> MACE::DataModel::PersistencyReader::CreateListFromTree() {
    TTree* tree = GetTree<Data_t>();
    std::vector<std::shared_ptr<Data_t>> dataList(0);
    dataList.reserve(tree->GetEntries());
    Data_t::ReadBranches(tree);
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        dataList.emplace_back(std::make_shared<Data_t>());
    }
    return dataList;
}