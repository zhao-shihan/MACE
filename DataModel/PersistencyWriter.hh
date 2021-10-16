#pragma once

#include "DataModel/Global.hh"
#include "DataModel/Base/PersistencyHandler.hh"
#include "DataModel/TreeNameHandler.hh"

class MACE::DataModel::PersistencyWriter :
    public MACE::DataModel::Base::PersistencyHandler {
    PersistencyWriter(const PersistencyWriter&) = delete;
    PersistencyWriter& operator=(const PersistencyWriter&) = delete;
public:
    PersistencyWriter();
    virtual ~PersistencyWriter();

    virtual void Open(const char* fileName, Option_t* = nullptr) override { PersistencyHandler::Open(fileName, "RECREATE"); }
    virtual void Close(Option_t* option = nullptr) override;

    template<class DataTypeInTree, class DataTypeInList>
    inline void CreateTree(const std::vector<DataTypeInList*>* dataList);
    template<class DataTypeInTree, class DataTypeInList>
    inline void CreateTree(const std::vector<DataTypeInList*>& dataList);
    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>* dataList) { CreateTree<DataType, DataType>(dataList); }
    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>& dataList) { CreateTree<DataType, DataType>(dataList); }
    void WriteTrees(Int_t option = 0, Int_t bufsize = 0);

private:
    std::vector<TTree*> fTrees;
};

template<class DataTypeInTree, class DataTypeInList>
inline void MACE::DataModel::PersistencyWriter::CreateTree(const std::vector<DataTypeInList*>* dataList) {
    static_assert(std::is_base_of_v<Base::Data, DataTypeInList>, "DataTypeInList should be derived from DataModel::Base::Data");
    static_assert(std::is_base_of_v<Base::Data, DataTypeInTree>, "DataTypeInTree should be derived from DataModel::Base::Data");
    static_assert(std::is_base_of_v<DataTypeInTree, DataTypeInList>, "DataTypeInList should be derived from DataTypeInTree");
    TString name = TreeNameHandler::GetName<DataTypeInTree>();
    TTree* tree = new TTree(name, name);
    DataTypeInTree::CreateBranches(tree);
    for (DataTypeInTree* data : *dataList) {
        data->FillBranches();
        tree->Fill();
    }
    fTrees.push_back(tree);
}

template<class DataTypeInTree, class DataTypeInList>
inline void MACE::DataModel::PersistencyWriter::CreateTree(const std::vector<DataTypeInList*>& dataList) {
    CreateTree<DataTypeInList, DataTypeInTree>(&dataList);
}