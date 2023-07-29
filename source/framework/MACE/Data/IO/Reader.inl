namespace MACE::Data::inline IO {

template<DataModel AModel, std::derived_from<TTree> ATree>
Reader<AModel, ATree>::const_iterator::const_iterator(const Reader* reader, gsl::index index) :
    fReader(reader),
    fIndex(index) {}

template<DataModel AModel, std::derived_from<TTree> ATree>
auto Reader<AModel, ATree>::const_iterator::operator-(const const_iterator& that) const -> difference_type {
    if (TreeAddress() != that.TreeAddress()) {
        throw std::logic_error(fmt::format("Trying to compare two iterators (LHS at {}, RHS at {}) "
                                           "pointing to different TTrees (LHS holds {} at index {}, "
                                           "RHS holds {} at index {})",
                                           this, &that,
                                           TreeAddress(), fIndex,
                                           that.TreeAddress(), that.fIndex));
    }
    return fIndex - that.fIndex;
}

template<DataModel AModel, std::derived_from<TTree> ATree>
auto Reader<AModel, ATree>::const_iterator::operator==(const const_iterator& that) const -> bool {
    return TreeAddress() == that.TreeAddress() and
           fIndex == that.fIndex;
}

template<DataModel AModel, std::derived_from<TTree> ATree>
auto Reader<AModel, ATree>::const_iterator::operator<=>(const const_iterator& that) const -> std::strong_ordering {
    const auto tree = TreeAddress();
    const auto thatTree = that.TreeAddress();
    return std::tie(tree, fIndex) <=> std::tie(thatTree, that.fIndex);
}

template<DataModel AModel, std::derived_from<TTree> ATree>
Reader<AModel, ATree>::Reader(ATree& tree) :
    Base(tree) {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        if ((... or (this->fTree.GetBranch(Field<Is>::Name().c_str()) == nullptr))) {
            throw std::runtime_error(fmt::format("Tree \"{}\" does not satisify the data model \"{}\"",
                                                 this->fTree.GetName(), AModel::Name()));
        }
        (..., this->fTree.SetBranchAddress(Field<Is>::Name().c_str(), FieldPointer<Is>()));
    }(gslx::make_index_sequence<AModel::NField()>());
}

} // namespace MACE::Data::inline IO
