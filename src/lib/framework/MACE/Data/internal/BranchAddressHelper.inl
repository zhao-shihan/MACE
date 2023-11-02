namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Entry> AEntry>
template<gsl::index I>
auto BranchAddressHelper<AEntry>::FieldPointer(AEntry& entry) {
    using ObjectType = typename AEntry::template Field<I>::Type;
    ObjectType& object = entry.template Get<I>();
    if constexpr (Concept::ROOTFundamental<ObjectType>) {
        return &object;
    } else if constexpr (IsStdArray<ObjectType>{}) {
        return object.data();
    } else if constexpr (IsFixedString<ObjectType>{}) {
        return object.CString();
    } else if constexpr (std::is_class_v<ObjectType>) {
        return &(fClassPointer[I] = std::addressof(object));
    }
}

} // namespace MACE::Data::internal
