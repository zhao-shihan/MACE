namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Tuple> ATuple>
template<CETAString AName>
auto BranchAddressHelper<ATuple>::ValuePointer(ATuple& tuple) -> auto {
    using ObjectType = typename ATuple::Model::template ValueOf<AName>::Type;
    ObjectType& object = Get<AName>(tuple);
    if constexpr (Concept::ROOTFundamental<ObjectType> or IsStdArray<ObjectType>{}) {
        return &object;
    } else if constexpr (IsFixedString<ObjectType>{}) {
        return object.CString();
    } else if constexpr (std::is_class_v<ObjectType>) {
        constexpr auto i = ATuple::Model::template Index<AName>();
        return &(std::get<i>(fClassPointer) = std::addressof(object));
    }
}

} // namespace MACE::Data::internal
