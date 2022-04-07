namespace MACE::Core {

template<IsTransientData Data_t>
TString DataFactory::GetTreeName(Long64_t treeIndex) const {
    return GetPrefixOfTreeName(treeIndex) + Data_t::BasicTreeName() + GetSuffixOfTreeName(treeIndex);
}

template<IsTransientData Data_t>
ObserverPtr<TTree> DataFactory::GetTree(TFile& file, Long64_t treeIndex) const {
    return file.Get<TTree>(GetTreeName<Data_t>(treeIndex));
}

template<IsTransientData Data_t, std::convertible_to<std::filesystem::path::string_type> Path_t>
std::shared_ptr<TChain> DataFactory::CreateChain(const std::vector<Path_t>& fileList, Long64_t treeIndex) const {
    auto chain = std::make_shared<TChain>(GetTreeName<Data_t>(treeIndex));
    for (auto&& file : fileList) {
        chain->Add(file.c_str());
    }
    return chain;
}

template<IsTransientData Data_t>
std::pair<Long64_t, Long64_t> DataFactory::GetTreeIndexRange(TFile& file) const {
    const auto maxKeys = file.GetNkeys();
    Long64_t beginIndex = 0;
    for (; file.GetKey(GetTreeName<Data_t>(beginIndex)) == nullptr; ++beginIndex) {
        if (beginIndex + 1 >= maxKeys) { return std::pair<Long64_t, Long64_t>(0, 0); }
    }
    Long64_t endIndex = beginIndex + 1;
    for (; file.GetKey(GetTreeName<Data_t>(endIndex)) != nullptr; ++endIndex) {}
    return std::make_pair(beginIndex, endIndex);
}

template<IsTransientData Data_t>
std::shared_ptr<TTree> DataFactory::CreateTree(Long64_t treeIndex) const {
    auto tree = std::make_shared<TTree>();
    tree->SetName(GetTreeName<Data_t>(treeIndex));
    tree->SetDirectory(nullptr);
    Data_t::CreateBranches(*tree);
    return tree;
}

template<IsTransientData DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
void DataFactory::FillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, TTree& tree, bool connected) {
    if (not connected) { DataInTree_t::ConnectToBranches(tree); }
    for (auto&& data : dataList) {
        static_cast<const DataInTree_t&>(*data).FillBranchSockets();
        tree.Fill();
    }
}

template<IsTransientData DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
void DataFactory::FillTree(const std::vector<DataInList_t*>& dataList, TTree& tree, bool connected) {
    //      A Trick, not means dataList should be observer
    //                          |
    //                          V
    FillTree<DataInTree_t, ObserverPtr, DataInList_t>(dataList, tree, connected);
}

template<IsTransientData DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, Long64_t treeIndex) const {
    auto tree = CreateTree<DataInTree_t>(treeIndex);
    FillTree<DataInTree_t, Pointer_t, DataInList_t>(dataList, *tree);
    return tree;
}

template<IsTransientData DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex) const {
    //                      A Trick, not means dataList should be observer
    //                                          |
    //                                          V
    return CreateAndFillTree<DataInTree_t, ObserverPtr, DataInList_t>(dataList, treeIndex);
}

template<IsTransientData Data_t>
std::vector<std::shared_ptr<Data_t>> DataFactory::CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected) {
    std::vector<std::shared_ptr<Data_t>> dataList(0);
    dataList.reserve(entriesRange.second - entriesRange.first);
    if (not connected) { Data_t::ConnectToBranches(tree); }
    for (Long64_t i = entriesRange.first; i < entriesRange.second; ++i) {
        tree.GetEntry(i);
        dataList.emplace_back(std::make_shared<Data_t>());
    }
    return dataList;
}

template<IsTransientData Data_t>
std::vector<std::shared_ptr<Data_t>> DataFactory::CreateAndFillList(TTree& tree, bool connected) {
    return CreateAndFillList<Data_t>(tree, std::make_pair<Long64_t, Long64_t>(0, tree.GetEntries()), connected);
}

template<IsTransientData Data_t>
std::vector<std::shared_ptr<Data_t>> DataFactory::CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<Data_t>(file, treeIndex);
    return CreateAndFillList<Data_t>(*tree, entriesRange, connected);
}

template<IsTransientData Data_t>
std::vector<std::shared_ptr<Data_t>> DataFactory::CreateAndFillList(TFile& file, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<Data_t>(file, treeIndex);
    return CreateAndFillList<Data_t>(*tree, connected);
}

} // namespace MACE::Core::DataModel
