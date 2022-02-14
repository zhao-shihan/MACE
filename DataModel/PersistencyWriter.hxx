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
    virtual ~PersistencyWriter() noexcept;

    // FIXME: allow option of both APPEND(?) and RECREATE
    void Open(const char* fileName) { PersistencyHandler::Open(fileName, "RECREATE"); }
    void Close(Option_t* option = nullptr);

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

#include "DataModel/PersistencyWriter.ixx"
