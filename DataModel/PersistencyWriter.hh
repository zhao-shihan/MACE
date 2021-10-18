#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Core/PersistencyHandler.hh"

class MACE::DataModel::PersistencyWriter :
    public MACE::DataModel::Core::PersistencyHandler {
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

    template<class DataTypeInTree, class DataTypeInList>
    TTree* CreateTreeFromList(const std::vector<DataTypeInList*>* dataList, TreeOperation behaviour = kDeleteAfterWrite);
    template<class DataTypeInTree, class DataTypeInList>
    TTree* CreateTreeFromList(const std::vector<DataTypeInList*>& dataList, TreeOperation behaviour = kDeleteAfterWrite) { return CreateTreeFromList<DataTypeInList, DataTypeInTree>(&dataList, behaviour); }
    template<class DataType>
    TTree* CreateTreeFromList(const std::vector<DataType*>* dataList, TreeOperation behaviour = kDeleteAfterWrite) { return CreateTreeFromList<DataType, DataType>(dataList, behaviour); }
    template<class DataType>
    TTree* CreateTreeFromList(const std::vector<DataType*>& dataList, TreeOperation behaviour = kDeleteAfterWrite) { return CreateTreeFromList<DataType, DataType>(&dataList, behaviour); }
    void AddTree(TTree* tree, TreeOperation behaviour = kJustWrite) { fTreeAndBehaviours.emplace_back(tree, behaviour); }

    void WriteTrees(Int_t option = 0, Int_t bufsize = 0);

private:
    std::vector<std::pair<TTree*, TreeOperation>> fTreeAndBehaviours;
};

template<class DataTypeInTree, class DataTypeInList>
TTree* MACE::DataModel::PersistencyWriter::CreateTreeFromList(const std::vector<DataTypeInList*>* dataList, TreeOperation behaviour) {
    static_assert(std::is_base_of_v<Core::Data, DataTypeInList>, "DataTypeInList should be derived from DataModel::Core::Data");
    static_assert(std::is_base_of_v<Core::Data, DataTypeInTree>, "DataTypeInTree should be derived from DataModel::Core::Data");
    static_assert(std::is_base_of_v<DataTypeInTree, DataTypeInList>, "DataTypeInList should be derived from DataTypeInTree");
    TString name = PersistencyHandler::GetTreeName<DataTypeInTree>();
    TTree* tree = new TTree(name, name);
    DataTypeInTree::CreateBranches(tree);
    for (DataTypeInTree* data : *dataList) {
        data->FillBranches();
        tree->Fill();
    }
    fTreeAndBehaviours.emplace_back(tree, behaviour);
    return tree;
}