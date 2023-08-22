namespace MACE::Data::inline IO {

template<DataModel AModel, std::derived_from<TTree> ATree>
Reader<AModel, ATree>::ConstIterator::ConstIterator(std::shared_ptr<const typename Reader<AModel, ATree>::Base::Essential> essential,
                                                    gsl::index index) :
    fEssential(std::move(essential)),
    fIndex(index) {}

template<DataModel AModel, std::derived_from<TTree> ATree>
auto Reader<AModel, ATree>::ConstIterator::operator-(const ConstIterator& that) const -> DifferenceType {
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
auto Reader<AModel, ATree>::ConstIterator::operator==(const ConstIterator& that) const -> bool {
    return TreeAddress() == that.TreeAddress() and
           fIndex == that.fIndex;
}

template<DataModel AModel, std::derived_from<TTree> ATree>
auto Reader<AModel, ATree>::ConstIterator::operator<=>(const ConstIterator& that) const -> std::strong_ordering {
    return std::tuple{TreeAddress(), fIndex} <=>
           std::tuple{that.TreeAddress(), that.fIndex};
}

template<DataModel AModel, std::derived_from<TTree> ATree>
Reader<AModel, ATree>::Reader(ATree& tree) :
    Base(tree) {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        if ((... or (this->Tree().GetBranch(Field<Is>::Name().c_str()) == nullptr))) {
            throw std::runtime_error(fmt::format("Tree \"{}\" does not satisify the data model \"{}\"",
                                                 this->Tree().GetName(), AModel::Name()));
        }
        (..., this->Tree().SetBranchAddress(Field<Is>::Name().c_str(), this->template FieldPointer<Is>()));
    }(gslx::make_index_sequence<AModel::NField()>());
}

} // namespace MACE::Data::inline IO
