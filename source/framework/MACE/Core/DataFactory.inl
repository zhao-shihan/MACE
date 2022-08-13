namespace MACE::Core {

template<IsTransientData AData>
TString DataFactory::GetTreeName(Long64_t treeIndex) const {
    return GetTreeNamePrefix(treeIndex) + AData::BasicTreeName() + GetTreeNameSuffix(treeIndex);
}

template<IsTransientData AData>
ObserverPtr<TTree> DataFactory::GetTree(TFile& file, Long64_t treeIndex) const {
    return file.Get<TTree>(GetTreeName<AData>(treeIndex));
}

template<IsTransientData AData, std::convertible_to<const char*> APath>
std::shared_ptr<TChain> DataFactory::CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex) const {
    auto chain = std::make_shared<TChain>(GetTreeName<AData>(treeIndex));
    for (auto&& file : fileList) {
        chain->AddFile(file);
    }
    return chain;
}

template<IsTransientData AData, typename APath> // clang-format off
    requires std::convertible_to<decltype(std::declval<APath>().c_str()), const char*>
std::shared_ptr<TChain> DataFactory::CreateChain(const std::vector<APath>& fileList, Long64_t treeIndex) const { // clang-format on
    auto chain = std::make_shared<TChain>(GetTreeName<AData>(treeIndex));
    for (auto&& file : fileList) {
        chain->AddFile(file.c_str());
    }
    return chain;
}

template<IsTransientData AData>
std::pair<Long64_t, Long64_t> DataFactory::GetTreeIndexRange(TFile& file) const {
    const auto maxKeys = file.GetNkeys();
    Long64_t beginIndex = 0;
    for (; file.GetKey(GetTreeName<AData>(beginIndex)) == nullptr; ++beginIndex) {
        if (beginIndex + 1 >= maxKeys) { return std::pair<Long64_t, Long64_t>(0, 0); }
    }
    Long64_t endIndex = beginIndex + 1;
    for (; file.GetKey(GetTreeName<AData>(endIndex)) != nullptr; ++endIndex) {}
    return std::make_pair(beginIndex, endIndex);
}

template<IsTransientData AData>
std::shared_ptr<TTree> DataFactory::CreateTree(Long64_t treeIndex) const {
    auto tree = std::make_shared<TTree>();
    tree->SetName(GetTreeName<AData>(treeIndex));
    tree->SetDirectory(nullptr);
    AData::CreateBranches(*tree);
    return tree;
}

template<IsTransientData ADataInTree, WeakPointerImitator ADataInListPointer> // clang-format off
    requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
void DataFactory::FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected) { // clang-format on
    if (not connected) { ADataInTree::ConnectToBranches(tree); }
    for (auto&& data : dataList) {
        static_cast<const ADataInTree&>(*data).FillBranchSockets();
        tree.Fill();
    }
}

template<WeakPointerImitator ADataInListPointer>
void DataFactory::FillTree(const std::vector<ADataInListPointer>& dataList, TTree& tree, bool connected) {
    FillTree<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInListPointer>(dataList, tree, connected);
}

template<IsTransientData ADataInTree, WeakPointerImitator ADataInListPointer> // clang-format off
    requires std::derived_from<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInTree>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex) const { // clang-format on
    auto tree = CreateTree<ADataInTree>(treeIndex);
    FillTree<ADataInTree, ADataInListPointer>(dataList, *tree, false);
    return tree;
}

template<WeakPointerImitator ADataInListPointer>
std::shared_ptr<TTree> DataFactory::CreateAndFillTree(const std::vector<ADataInListPointer>& dataList, Long64_t treeIndex) const {
    return CreateAndFillTree<typename std::pointer_traits<ADataInListPointer>::element_type, ADataInListPointer>(dataList, treeIndex);
}

template<IsTransientData AData>
std::vector<std::shared_ptr<AData>> DataFactory::CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected) {
    std::vector<std::shared_ptr<AData>> dataList(0);
    dataList.reserve(entriesRange.second - entriesRange.first);
    if (not connected) { AData::ConnectToBranches(tree); }
    for (Long64_t i = entriesRange.first; i < entriesRange.second; ++i) {
        tree.GetEntry(i);
        dataList.emplace_back(std::make_shared<AData>());
    }
    return dataList;
}

template<IsTransientData AData>
std::vector<std::shared_ptr<AData>> DataFactory::CreateAndFillList(TTree& tree, bool connected) {
    return CreateAndFillList<AData>(tree, std::make_pair<Long64_t, Long64_t>(0, tree.GetEntries()), connected);
}

template<IsTransientData AData>
std::vector<std::shared_ptr<AData>> DataFactory::CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<AData>(file, treeIndex);
    return CreateAndFillList<AData>(*tree, entriesRange, connected);
}

template<IsTransientData AData>
std::vector<std::shared_ptr<AData>> DataFactory::CreateAndFillList(TFile& file, Long64_t treeIndex, bool connected) const {
    auto tree = GetTree<AData>(file, treeIndex);
    return CreateAndFillList<AData>(*tree, connected);
}

} // namespace MACE::Core
