namespace MACE::Data::inline IO {

template<DataModel AModel>
Reader<AModel>::ConstIterator::ConstIterator(const typename Reader<AModel>::Essential& essential, gsl::index index) :
    ConstIterator{&essential, index} {}

template<DataModel AModel>
Reader<AModel>::ConstIterator::ConstIterator(const typename Reader<AModel>::Essential* essential, gsl::index index) :
    fEssential{essential},
    fIndex{index} {}

template<DataModel AModel>
auto Reader<AModel>::ConstIterator::operator-(const ConstIterator& that) const -> DifferenceType {
    if (TreeAddress() != that.TreeAddress()) {
        throw std::logic_error{fmt::format("Trying to compare two iterators (LHS at {}, RHS at {}) "
                                           "pointing to different TTrees (LHS holds {} at index {}, "
                                           "RHS holds {} at index {})",
                                           this, &that,
                                           TreeAddress(), fIndex,
                                           that.TreeAddress(), that.fIndex)};
    }
    return fIndex - that.fIndex;
}

template<DataModel AModel>
Reader<AModel>::Reader(TTree& tree) :
    Base(tree) {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        if ((... or (this->Tree().GetBranch(Field<Is>::Name().c_str()) == nullptr))) {
            throw std::runtime_error(fmt::format("Tree \"{}\" does not satisify the data model \"{}\"",
                                                 this->Tree().GetName(), AModel::Name()));
        }
        (..., this->Tree().SetBranchAddress(Field<Is>::Name().c_str(), this->template FieldPointer<Is>()));
    }(gslx::make_index_sequence<AModel::NField()>());
}

template<DataModel AModel>
template<template<typename, typename...> typename ASequenceContainer>
auto Reader<AModel>::IteratorCollection() const -> ASequenceContainer<Iterator> {
    ASequenceContainer<Iterator> data(Size());
    Iterator iterator = {this->fEssential, -1};
    std::ranges::generate(data, [&iterator] { return ++iterator; });
    return data;
}

} // namespace MACE::Data::inline IO
