template<typename Object_t, typename Address_t>
MACE::DataModel::Interface::BranchSocket<Object_t, Address_t>::
BranchSocket(const char* branchName) :
    fBranchName(branchName),
    fConnectedTree(nullptr) {}

template<typename Object_t, typename Address_t>
void MACE::DataModel::Interface::BranchSocket<Object_t, Address_t>::
CreateBranch(TTree& tree) {
    fConnectedTree = std::addressof(tree);
    tree.Branch(fBranchName, Address());
}

template<typename Object_t, typename Address_t>
void MACE::DataModel::Interface::BranchSocket<Object_t, Address_t>::
ConnectToBranch(TTree& tree) {
    if (std::addressof(tree) != fConnectedTree) {
        fConnectedTree = std::addressof(tree);
        tree.SetBranchAddress(fBranchName, Address());
    }
}
