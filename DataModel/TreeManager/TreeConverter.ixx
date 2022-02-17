template<class DataInTree_t, class DataInList_t>
inline std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::TreeManager::TreeConverter::
CreateList(const std::shared_ptr<TTree>& tree) {
    return CreateList<DataInTree_t, DataInList_t, decltype(tree)>(tree);
}

template<class DataInTree_t, class DataInList_t>
inline std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::TreeManager::TreeConverter::
CreateList(TTree* tree) {
    return CreateList<DataInTree_t, DataInList_t, decltype(tree)>(tree);
}

template<class DataInTree_t, class DataInList_t, typename PointerOfTree_t>
std::vector<std::shared_ptr<DataInList_t>> MACE::DataModel::TreeManager::TreeConverter::
CreateList(PointerOfTree_t tree) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<DataInList_t, DataInTree_t>,
        "DataInList_t should be the base of DataInTree_t");
    std::vector<std::shared_ptr<DataInList_t>> dataList(0);
    auto entries = tree->GetEntries();
    dataList.reserve(entries);
    DataInList_t::ReadBranches(tree);
    for (Long64_t i = 0; i < entries; ++i) {
        tree->GetEntry(i);
        dataList.emplace_back(std::make_shared<DataInList_t>());
    }
    return dataList;
}
