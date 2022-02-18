template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::DataHub::
FindTree(TFile& file, Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, Data_t>,
        "Data_t should be derived from DataModel::Interface::Data.");
    return file.Get<TTree>(GetTreeName<Data_t>(treeIndex));
}

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::DataHub::
FindTree(const std::unique_ptr<TFile>& file, Long64_t treeIndex) {
    return FindTree<Data_t>(*file, treeIndex);
}

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::DataHub::
FindTree(const std::shared_ptr<TFile>& file, Long64_t treeIndex) {
    return FindTree<Data_t>(*file, treeIndex);
}

template<class Data_t>
inline MACE::ObserverPtr<TTree> MACE::DataModel::DataHub::
FindTree(TFile* file, Long64_t treeIndex) {
    return FindTree<Data_t>(*file, treeIndex);
}

template<class DataInList_t, class DataInTree_t>
inline std::shared_ptr<TTree> MACE::DataModel::DataHub::
CreateTree(const std::vector<std::shared_ptr<DataInList_t>>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInList_t, DataInTree_t, std::shared_ptr<DataInList_t>>(dataList, treeIndex);
}

template<class DataInList_t, class DataInTree_t>
inline std::shared_ptr<TTree> MACE::DataModel::DataHub::
CreateTree(const std::vector<std::shared_ptr<const DataInList_t>>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInList_t, DataInTree_t, std::shared_ptr<const DataInList_t>>(dataList, treeIndex);
}

template<class DataInList_t, class DataInTree_t>
inline std::shared_ptr<TTree> MACE::DataModel::DataHub::
CreateTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInList_t, DataInTree_t, DataInList_t*>(dataList, treeIndex);
}

template<class DataInList_t, class DataInTree_t>
inline std::shared_ptr<TTree> MACE::DataModel::DataHub::
CreateTree(const std::vector<const DataInList_t*>& dataList, Long64_t treeIndex) {
    return CreateTreeCore<DataInList_t, DataInTree_t, const DataInList_t*>(dataList, treeIndex);
}

template<class DataInTree_t, class DataInList_t>
std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::DataHub::
CreateList(TTree& tree) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data.");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data.");
    static_assert(std::is_base_of_v<DataInList_t, DataInTree_t>,
        "DataInList_t should be the base of DataInTree_t.");
    std::vector<std::shared_ptr<DataInList_t>> dataList(0);
    auto entries = tree.GetEntries();
    dataList.reserve(entries);
    DataInList_t::ReadBranches(tree);
    for (Long64_t i = 0; i < entries; ++i) {
        tree.GetEntry(i);
        dataList.emplace_back(std::make_shared<DataInList_t>());
    }
    return dataList;
}

template<class DataInTree_t, class DataInList_t>
inline std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::DataHub::
CreateList(const std::unique_ptr<TTree>& tree) {
    return CreateList<DataInTree_t, DataInList_t>(*tree);
}

template<class DataInTree_t, class DataInList_t>
inline std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::DataHub::
CreateList(const std::shared_ptr<TTree>& tree) {
    return CreateList<DataInTree_t, DataInList_t>(*tree);
}

template<class DataInTree_t, class DataInList_t>
inline std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::DataHub::
CreateList(TTree* tree) {
    return CreateList<DataInTree_t, DataInList_t>(*tree);
}

template<class DataInList_t, class DataInTree_t, class PointerOfDataInList_t>
std::shared_ptr<TTree> MACE::DataModel::DataHub::
CreateTreeCore(const std::vector<PointerOfDataInList_t>& dataList, Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data.");
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data.");
    static_assert(std::is_base_of_v<DataInTree_t, DataInList_t>,
        "DataInTree_t should be the base of DataInList_t.");
    auto tree = std::make_shared<TTree>();
    tree->SetName(GetTreeName<DataInTree_t>(treeIndex));
    tree->SetDirectory(nullptr);
    DataInTree_t::CreateBranches(*tree);
    for (auto&& data : dataList) {
        static_cast<const DataInTree_t&>(*data).FillBranchVariables();
        tree->Fill();
    }
    return tree;
}
