namespace MACE::DataModel::inline Column {

template<class AData, gsl::index AUniqueID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
StringColumn<AData, AUniqueID, AMaxSize, T>::StringColumn() :
    Base(),
    fString(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Column
