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
                                           "and RHS refers to entry {} in (TTree&)@{} (Name: {} Title: {})",
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
        (...,
         [this] {
             if (this->Tree().GetBranch(Field<Is>::Name().c_str()) == nullptr) {
                 throw std::invalid_argument(fmt::format("TTree named {} does not meet the data model {} due to the absence of field {}",
                                                         this->Tree().GetName(), AModel::Name(), Field<Is>::Name()));
             }
         }());
    }(gslx::make_index_sequence<AModel::NField()>());
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (...,
         [this] {
             TBranch* branch;
             this->Tree().SetBranchAddress(Field<Is>::Name().c_str(), this->template FieldPointer<Is>(), &branch);
             branch->SetAutoDelete(false);
         }());
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
