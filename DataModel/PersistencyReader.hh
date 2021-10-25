#pragma once

#include "ROOT/RDataFrame.hxx"

#include "DataModel/Global.hh"
#include "DataModel/Core/PersistencyHandler.hh"

class MACE::DataModel::PersistencyReader :
    public MACE::DataModel::Core::PersistencyHandler {
    PersistencyReader(const PersistencyReader&) = delete;
    PersistencyReader& operator=(const PersistencyReader&) = delete;
public:
    PersistencyReader();
    PersistencyReader(const char* fileName);
    virtual ~PersistencyReader() {}

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "READ"); }
    virtual void Close(Option_t* option = nullptr) { PersistencyHandler::Close(option); }

    template<class DataType>
    typename std::enable_if_t<std::is_class_v<DataType>, std::vector<DataType>> CreateListFromTree();
    template<class DataPointer>
    typename std::enable_if_t<std::is_pointer_v<DataPointer>, std::vector<DataPointer>> CreateListFromTree();
    template<class DataType>
    TTree* GetTree() { return fFile->Get<TTree>(GetTreeName<DataType>()); }
};

template<class DataType>
typename std::enable_if_t<std::is_class_v<DataType>, std::vector<DataType>>
MACE::DataModel::PersistencyReader::CreateListFromTree() {
    std::vector<DataType> dataList(0);
    TTree* tree = GetTree<DataType>();
    DataType::ReadBranches(tree);
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        dataList.emplace_back();
    }
    return dataList;
}

template<class DataPointer>
typename std::enable_if_t<std::is_pointer_v<DataPointer>, std::vector<DataPointer>>
MACE::DataModel::PersistencyReader::CreateListFromTree() {
    using DataType = std::remove_pointer_t<DataPointer>;
    std::vector<DataPointer> dataList(0);
    TTree* tree = GetTree<DataType>();
    DataType::ReadBranches(tree);
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry();
        dataList.emplace_back(new DataType());
    }
    return dataList;
}