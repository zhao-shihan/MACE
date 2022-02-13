template<class DataInTree_t, class DataInList_t>
std::pair<std::vector<std::shared_ptr<DataInList_t>>, TTree*> MACE::DataModel::PersistencyReader::CreateListFromTree(Long64_t treeIndex) {
    static_assert(std::is_base_of_v<Interface::Data, DataInTree_t>,
        "DataInTree_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<Interface::Data, DataInList_t>,
        "DataInList_t should be derived from DataModel::Interface::Data");
    static_assert(std::is_base_of_v<DataInList_t, DataInTree_t>,
        "DataInList_t should be the base of DataInTree_t");
    std::vector<std::shared_ptr<DataInList_t>> dataList(0);
    TTree* tree = GetTree<DataInTree_t>(treeIndex);
    if (tree != nullptr) {
        dataList.reserve(tree->GetEntries());
        DataInList_t::ReadBranches(tree);
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);
            dataList.emplace_back(std::make_shared<DataInList_t>());
        }
    }
    return std::make_pair(dataList, tree);
}
