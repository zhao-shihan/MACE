#pragma once

#include "TFile.h"
#include "TFolder.h"

#include "DataModelGlobal.hh"

class MACE::DataModel::PersistencyWriter {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(PersistencyWriter);
public:
    PersistencyWriter();
    ~PersistencyWriter();

    void Open(const char* fileName);
    void Close(Option_t* option = nullptr);

    void SetNamePrefix(const TString& prefix) { fPrefix = prefix; }
    void SetNamePrefix(TString&& prefix) { fPrefix = std::move(prefix); }
    void SetNameSuffix(const TString& suffix) { fSuffix = suffix; }
    void SetNameSuffix(TString&& suffix) { fSuffix = std::move(suffix); }

    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>* dataList);
    template<class DataType>
    inline void CreateTree(const std::vector<DataType*>& dataList);
    void WriteTrees(Int_t option = 0, Int_t bufsize = 0);

private:
    TFile* fFile;
    std::vector<TTree*> fTrees;
    TString fPrefix;
    TString fSuffix;
};

template<class DataType>
inline void MACE::DataModel::PersistencyWriter::CreateTree(const std::vector<DataType*>* dataList) {
    TString name = fPrefix + DataType::name + fSuffix;
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