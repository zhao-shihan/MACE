#include "TFile.h"

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::TreeProvider::
FindTree(const std::unique_ptr<TFile>& file, Long64_t treeIndex) {
    return FindTreeCore<Data_t, decltype(file)>(file, treeIndex);
}

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::TreeProvider::
FindTree(const std::shared_ptr<TFile>& file, Long64_t treeIndex) {
    return FindTreeCore<Data_t, decltype(file)>(file, treeIndex);
}

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::TreeProvider::
FindTree(TFile* file, Long64_t treeIndex) {
    return FindTreeCore<Data_t, decltype(file)>(file, treeIndex);
}

template<class DataInTree_t, class DataInList_t>
inline std::shared_ptr<TTree> MACE::DataModel::TreeProvider::
CreateTree(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInTree_t, DataInList_t, std::shared_ptr<DataInList_t>>(dataList, treeIndex);
}

template<class DataInTree_t, class DataInList_t>
inline std::shared_ptr<TTree> MACE::DataModel::TreeProvider::
CreateTree(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInTree_t, DataInList_t, std::shared_ptr<const DataInList_t>>(dataList, treeIndex);
}

template<class DataInTree_t, class DataInList_t>
inline std::shared_ptr<TTree> MACE::DataModel::TreeProvider::
CreateTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInTree_t, DataInList_t, DataInList_t*>(dataList, treeIndex);
}

template<class DataInTree_t, class DataInList_t>
inline std::shared_ptr<TTree> MACE::DataModel::TreeProvider::
CreateTree(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInTree_t, DataInList_t, const DataInList_t*>(dataList, treeIndex);
}

template<class Data_t, class PointerOfFile_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::TreeProvider::
FindTreeCore(PointerOfFile_t file, Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, Data_t>,
        "Data_t should be derived from DataModel::Interface::Data");
    return file->TFile::Get<TTree>(GetFullTreeName<Data_t>(treeIndex));
}

template<class DataInTree_t, class DataInList_t, class PointerOfDataInTree_t>
std::shared_ptr<TTree> MACE::DataModel::TreeProvider::
CreateTreeCore(const std::vector<PointerOfDataInTree_t>& dataList, Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<DataInTree_t, DataInList_t>,
        "DataInList_t should be derived from DataInTree_t");
    TString name = GetFullTreeName<DataInTree_t>(treeIndex);
    auto tree = std::make_shared<TTree>(name, name);
    DataInTree_t::CreateBranches(tree);
    for (auto&& data : dataList) {
        data->FillBranches();
        tree->Fill();
    }
    return tree;
}
