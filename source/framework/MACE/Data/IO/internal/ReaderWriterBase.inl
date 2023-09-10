namespace MACE::Data::inline IO::internal {

template<DataModel AModel>
ReaderWriterBase<AModel>::ReaderWriterBase(TTree& tree) :
    NonMoveableBase{},
    fEssential{tree, {}},
    fClassPointerStorage{},
    fFieldPointerList{
        [this]<gsl::index... Is>(gslx::index_sequence<Is...>) -> decltype(fFieldPointerList) {
            return {[this] {
                FieldType<Is>& object = fEssential.entry.template Get<Is>();
                if constexpr (Concept::ROOTFundamental<FieldType<Is>>) {
                    return &object;
                } else if constexpr (detail::IsStdArray<FieldType<Is>>::value) {
                    return object.data();
                } else if constexpr (detail::IsFixedString<FieldType<Is>>::value) {
                    return object.CString();
                } else if constexpr (std::is_class_v<FieldType<Is>>) {
                    return &fClassPointerStorage.emplace_back(std::addressof(object));
                }
            }()...};
        }(gslx::make_index_sequence<AModel::NField()>{})} {}

template<DataModel AModel>
ReaderWriterBase<AModel>::~ReaderWriterBase() {
    [this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (..., Tree().ResetBranchAddress(Tree().GetBranch(Field<Is>::Name().c_str())));
    }(gslx::make_index_sequence<AModel::NField()>{});
}

} // namespace MACE::Data::inline IO::internal
