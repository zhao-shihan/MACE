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

    template<class DataType>
    std::vector<std::shared_ptr<DataType>> CreateListFromTree();
    template<class DataType>
    TTree* GetTree() { return fFile->Get<TTree>(GetTreeName<DataType>()); }
};

template<class DataType>
std::vector<std::shared_ptr<DataType>> MACE::DataModel::PersistencyReader::CreateListFromTree() {
    TTree* tree = GetTree<DataType>();
    std::vector<std::shared_ptr<DataType>> dataList(0);
    dataList.reserve(tree->GetEntries());
    DataType::ReadBranches(tree);
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        dataList.emplace_back(std::make_shared<DataType>());
    }
    return dataList;
}