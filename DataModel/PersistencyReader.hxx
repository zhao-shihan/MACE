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

#include "DataModel/PersistencyReader.ixx"
