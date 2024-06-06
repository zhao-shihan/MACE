namespace MACE::Data::internal {

template<Concept::InstantiatedFrom<Tuple> ATuple>
BranchHelper<ATuple>::BranchHelper(ATuple& tuple) :
    fTuple{&tuple},
    fClassPointer{} {}

template<Concept::InstantiatedFrom<Tuple> ATuple>
template<muc::ceta_string AName>
auto BranchHelper<ATuple>::CreateBranch(std::derived_from<TTree> auto& tree) -> TBranch* {
    using ObjectType = typename ATuple::Model::template ValueOf<AName>::Type;
    ObjectType& object{*Get<AName>(*fTuple)};
    if constexpr (Concept::ROOTFundamental<ObjectType> or IsStdArray<ObjectType>{}) {
        return tree.Branch(AName, &object);
    } else if constexpr (IsFixedString<ObjectType>{}) {
        return tree.Branch(AName, object.CString(), (AName.String() + "/C").c_str());
    } else if constexpr (std::is_class_v<ObjectType>) {
        constexpr auto i = ATuple::Model::template Index<AName>();
        return tree.Branch(AName, &(std::get<i>(fClassPointer) = std::addressof(object)));
    }
}

template<Concept::InstantiatedFrom<Tuple> ATuple>
template<muc::ceta_string AName>
auto BranchHelper<ATuple>::ConnectBranch(std::derived_from<TTree> auto& tree) -> std::pair<int, TBranch*> {
    using ObjectType = typename ATuple::Model::template ValueOf<AName>::Type;
    ObjectType& object{*Get<AName>(*fTuple)};
    int ec{};
    TBranch* branch{};
    if constexpr (Concept::ROOTFundamental<ObjectType> or IsStdArray<ObjectType>{}) {
        ec = tree.SetBranchAddress(AName, &object, &branch);
    } else if constexpr (IsFixedString<ObjectType>{}) {
        ec = tree.SetBranchAddress(AName, object.CString(), &branch);
    } else if constexpr (std::is_class_v<ObjectType>) {
        constexpr auto i{ATuple::Model::template Index<AName>()};
        ec = tree.SetBranchAddress(AName, &(std::get<i>(fClassPointer) = std::addressof(object)), &branch);
    }
    return {ec, branch};
}

template<Concept::InstantiatedFrom<Tuple> ATuple>
template<muc::ceta_string AName>
auto BranchHelper<ATuple>::ConnectBranchNoCheck(std::derived_from<TTree> auto& tree) -> TBranch* {
    using ObjectType = typename ATuple::Model::template ValueOf<AName>::Type;
    ObjectType& object{*Get<AName>(*fTuple)};
    void* objectPointer{};
    if constexpr (Concept::ROOTFundamental<ObjectType> or IsStdArray<ObjectType>{}) {
        objectPointer = &object;
    } else if constexpr (IsFixedString<ObjectType>{}) {
        objectPointer = object.CString();
    } else if constexpr (std::is_class_v<ObjectType>) {
        constexpr auto i{ATuple::Model::template Index<AName>()};
        objectPointer = &(std::get<i>(fClassPointer) = std::addressof(object));
    }
    TBranch* branch{};
    tree.SetBranchAddress(AName, objectPointer, &branch);
    return branch;
}

} // namespace MACE::Data::internal
