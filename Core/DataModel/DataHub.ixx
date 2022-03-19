namespace MACE::DataModel {

    template<std::derived_from<Interface::Transient> Data_t>
    inline TString DataHub::GetTreeName(Long64_t treeIndex) const {
        return GetPrefixOfTreeName(treeIndex) + static_cast<const char*>(Data_t::BasicName()) + GetSuffixOfTreeName(treeIndex);
    }

    template<std::derived_from<Interface::Transient> Data_t>
    inline MACE::ObserverPtr<TTree> DataHub::GetTree(TFile& file, Long64_t treeIndex) {
        return file.Get<TTree>(GetTreeName<Data_t>(treeIndex));
    }

    template<std::derived_from<Interface::Transient> Data_t>
    std::pair<Long64_t, Long64_t> DataHub::GetTreeIndexRange(TFile& file) {
        const auto maxKeys = file.GetNkeys();
        Long64_t beginIndex = 0;
        for (; file.GetKey(GetTreeName<Data_t>(beginIndex)) == nullptr; ++beginIndex) {
            if (beginIndex + 1 >= maxKeys) { return std::pair<Long64_t, Long64_t>(0, 0); }
        }
        Long64_t endIndex = beginIndex + 1;
        for (; file.GetKey(GetTreeName<Data_t>(endIndex)) != nullptr; ++endIndex);
        return std::make_pair(beginIndex, endIndex);
    }

    template<std::derived_from<Interface::Transient> Data_t>
    inline std::shared_ptr<TTree> DataHub::CreateTree(Long64_t treeIndex) {
        auto tree = std::make_shared<TTree>();
        tree->SetName(GetTreeName<Data_t>(treeIndex));
        tree->SetDirectory(nullptr);
        Data_t::CreateBranches(*tree);
        return tree;
    }

    template<std::derived_from<Interface::Transient> DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    void DataHub::FillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, TTree& tree, bool connected) {
        if (not connected) { DataInTree_t::ConnectToBranches(tree); }
        for (auto&& data : dataList) {
            static_cast<const DataInTree_t&>(*data).FillBranchSockets();
            tree.Fill();
        }
    }

    template<std::derived_from<Interface::Transient> DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    inline void DataHub::FillTree(const std::vector<DataInList_t*>& dataList, TTree& tree, bool connected) {
        //      A Trick, not means dataList should be observer
        //                          |
        //                          V
        FillTree<DataInTree_t, ObserverPtr, DataInList_t>(dataList, tree, connected);
    }

    template<std::derived_from<Interface::Transient> DataInTree_t, template<class T> typename Pointer_t, std::derived_from<DataInTree_t> DataInList_t>
    inline std::shared_ptr<TTree> DataHub::CreateAndFillTree(const std::vector<Pointer_t<DataInList_t>>& dataList, Long64_t treeIndex) {
        auto tree = CreateTree<DataInTree_t>(treeIndex);
        FillTree<DataInTree_t, Pointer_t, DataInList_t>(dataList, *tree);
        return tree;
    }

    template<std::derived_from<Interface::Transient> DataInTree_t, std::derived_from<DataInTree_t> DataInList_t>
    inline std::shared_ptr<TTree> DataHub::CreateAndFillTree(const std::vector<DataInList_t*>& dataList, Long64_t treeIndex) {
        //                      A Trick, not means dataList should be observer
        //                                          |
        //                                          V
        return CreateAndFillTree<DataInTree_t, ObserverPtr, DataInList_t>(dataList, treeIndex);
    }

    template<std::derived_from<Interface::Transient> Data_t>
    std::vector<std::shared_ptr<Data_t>> DataHub::CreateAndFillList(TTree& tree, const std::pair<Long64_t, Long64_t>& entriesRange, bool connected) {
        std::vector<std::shared_ptr<Data_t>> dataList(0);
        dataList.reserve(entriesRange.second - entriesRange.first);
        if (not connected) { Data_t::ConnectToBranches(tree); }
        for (Long64_t i = entriesRange.first; i < entriesRange.second; ++i) {
            tree.GetEntry(i);
            dataList.emplace_back(std::make_shared<Data_t>());
        }
        return dataList;
    }

    template<std::derived_from<Interface::Transient> Data_t>
    inline std::vector<std::shared_ptr<Data_t>> DataHub::CreateAndFillList(TTree& tree, bool connected) {
        return CreateAndFillList<Data_t>(tree, std::make_pair<Long64_t, Long64_t>(0, tree.GetEntries()), connected);
    }

    template<std::derived_from<Interface::Transient> Data_t>
    inline std::vector<std::shared_ptr<Data_t>> DataHub::CreateAndFillList(TFile& file, const std::pair<Long64_t, Long64_t>& entriesRange, Long64_t treeIndex, bool connected) {
        auto tree = GetTree<Data_t>(file, treeIndex);
        return CreateAndFillList<Data_t>(*tree, entriesRange, connected);
    }

    template<std::derived_from<Interface::Transient> Data_t>
    inline std::vector<std::shared_ptr<Data_t>> DataHub::CreateAndFillList(TFile& file, Long64_t treeIndex, bool connected) {
        auto tree = GetTree<Data_t>(file, treeIndex);
        return CreateAndFillList<Data_t>(*tree, connected);
    }

}
