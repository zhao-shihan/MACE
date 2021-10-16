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

    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>* dataList);
    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>& dataList);
    void WriteTrees(Int_t option = 0, Int_t bufsize = 0);

private:
    std::vector<TTree*> fTrees;
};

template<class DataType>
inline void MACE::DataModel::PersistencyWriter::CreateTree(const std::vector<DataType*>* dataList) {
    static_assert(std::is_base_of_v<Base::Data, DataType>, "DataType should be derived from DataModel::Base::Data");
    TString name = TreeNameHandler::GetName<DataType>();
    TTree* tree = new TTree(name, name);
    DataType::CreateBranches(tree);
    for (DataType* data : *dataList) {
        data->FillBranches();
        tree->Fill();
    }
    fTrees.push_back(tree);
}

template<class DataType>
inline void MACE::DataModel::PersistencyWriter::CreateTree(const std::vector<DataType*>& dataList) {
    CreateTree<DataType>(&dataList);
}