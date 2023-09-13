namespace MACE::Data::inline IO {

template<Modelized AModel>
Reader<AModel>::Iterator::Iterator(gsl::index index, const typename Reader<AModel>::Essential& essential) :
    Iterator{index, &essential} {}

template<Modelized AModel>
Reader<AModel>::Iterator::Iterator(gsl::index index, const typename Reader<AModel>::Essential* essential) :
    fIndex{index},
    fEssential{essential} {}

template<Modelized AModel>
auto Reader<AModel>::Iterator::operator-(const Iterator& that) const -> DifferenceType {
    if (&Tree() != &that.Tree()) {
        throw std::logic_error{fmt::format("Attempting to subtract two data reader iterators (LHS at {}, RHS at {}) "
                                           "referring to different TTree! LHS refers to entry {} in (TTree&)@{} (Name: {} Title: {}), "
                                           "and RHS refers to entry {} in (TTree&)@{} (Name: {} Title: {}).",
                                           this, &that,
                                           fIndex, &Tree(), Tree()->GetName(), Tree()->GetTitle(),
                                           that.fIndex, &that.Tree(), that.Tree()->GetName(), that.Tree()->GetTitle())};
    }
    return fIndex - that.fIndex;
}

template<Modelized AModel>
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

template<Modelized AModel>
template<template<typename, typename...> typename ASequenceContainer>
auto Reader<AModel>::IteratorCollection() const -> ASequenceContainer<Iterator> {
    ASequenceContainer<Iterator> data(Size());
    std2b::ranges::iota(data, Begin());
    return data;
}

} // namespace MACE::Data::inline IO
