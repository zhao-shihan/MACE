namespace MACE::Core {

template<IsTransientData DataT>
TString DataFactory::GetTreeName(Long64_t treeIndex) const {
    return GetTreeNamePrefix(treeIndex) + DataT::BasicTreeName() + GetTreeNameSuffix(treeIndex);
}

template<IsTransientData DataT>
ObserverPtr<TTree> DataFactory::GetTree(TFile& file, Long64_t treeIndex) const {
    return file.Get<TTree>(GetTreeName<DataT>(treeIndex));
}

template<IsTransientData DataT, std::convertible_to<std::filesystem::path::string_type> PathT>
std::shared_ptr<TChain> DataFactory::CreateChain(const std::vector<PathT>& fileList, Long64_t treeIndex) const {
    auto chain = std::make_shared<TChain>(GetTreeName<DataT>(treeIndex));
    for (auto&& file : fileList) {
        chain->Add(file.c_str());
    }
    return chain;
}

template<IsTransientData DataT>
std::pair<Long64_t, Long64_t> DataFactory::GetTreeIndexRange(TFile& file) const {
    const auto maxKeys = file.GetNkeys();
    Long64_t beginIndex = 0;
    for (; file.GetKey(GetTreeName<DataT>(beginIndex)) == nullptr; ++beginIndex) {
        if (beginIndex + 1 >= maxKeys) { return std::pair<Long64_t, Long64_t>(0, 0); }
    }
    Long64_t endIndex = beginIndex + 1;
    for (; file.GetKey(GetTreeName<DataT>(endIndex)) != nullptr; ++endIndex) {}
    return std::make_pair(beginIndex, endIndex);
}

template<IsTransientData DataT>
std::shared_ptr<TTree> DataFactory::CreateTree(Long64_t treeIndex) const {
    auto tree = std::make_shared<TTree>();
    tree->SetName(GetTreeName<DataT>(treeIndex));
    tree->SetDirectory(nullptr);
    DataT::CreateBranches(*tree);
    return tree;
}

template<IsTransientData DataInTreeT, template<class T, class... _> typename PointerT, std::derived_from<DataInTreeT> DataInListT>
void DataFactory::FillTree(const std::vector<PointerT<DataInListT>>& dataList, TTree& tree, bool connected) {
    if (not connected) { DataInTreeT::ConnectToBranches(tree); }
    for (auto&& data : dataList) {
        static_cast<const DataInTreeT&>(*data).FillBranchSockets();
        tree.Fill();
    }
}

template<IsTransientData DataInTreeT, std::derived_from<DataInTreeT> DataInListT>
void DataFactory::FillTree(const std::vector<DataInListT*>& dataList, TTree& tree, bool connected) {
    //      A Trick, not means dataList should be observer
    //                          |
    //                          V
    FillTree<DataInTreeT, ObserverPtr, DataInListT>(dataList, tree, connected);
}

template<IsTransientData DataInTreeT, template<class T, class... _> typename PointerT, std::derived_from<DataInTreeT> DataInListT>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<PointerT<DataInListT>>& dataList, Long64_t treeIndex) const {
    auto tree = CreateTree<DataInTreeT>(treeIndex);
    FillTree<DataInTreeT, PointerT, DataInListT>(dataList, *tree);
    return tree;
}

template<IsTransientData DataInTreeT, std::derived_from<DataInTreeT> DataInListT>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<DataInListT*>& dataList, Long64_t treeIndex) const {
    //                      A Trick, not means dataList should be observer
    //                                          |
    //                                          V
    return CreateAndFillTree<DataInTreeT, ObserverPtr, DataInListT>(dataList, treeIndex);
}

template<IsTransientData DataT>
std::vector<std::shared_ptr<DataT>> DataFactory::CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected) {
    std::vector<std::shared_ptr<DataT>> dataList(0);
    dataList.reserve(entriesRange.second - entriesRange.first);
    if (not connected) { DataT::ConnectToBranches(tree); }
    for (Long64_t i = entriesRange.first; i < entriesRange.second; ++i) {
        tree.GetEntry(i);
        dataList.emplace_back(std::make_shared<DataT>());
    }
    return dataList;
}

template<IsTransientData DataT>
std::vector<std::shared_ptr<DataT>> DataFactory::CreateAndFillList(TTree& tree, bool connected) {
    return CreateAndFillList<DataT>(tree, std::make_pair<Long64_t, Long64_t>(0, tree.GetEntries()), connected);
}

template<IsTransientData DataT>
std::vector<std::shared_ptr<DataT>> DataFactory::CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<DataT>(file, treeIndex);
    return CreateAndFillList<DataT>(*tree, entriesRange, connected);
}

template<IsTransientData DataT>
std::vector<std::shared_ptr<DataT>> DataFactory::CreateAndFillList(TFile& file, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<DataT>(file, treeIndex);
    return CreateAndFillList<DataT>(*tree, connected);
}

} // namespace MACE::Core
