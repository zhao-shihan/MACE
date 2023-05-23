namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index AUniqueID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
StringEntry<AData, AUniqueID, AMaxSize, T>::StringEntry() :
    Base(),
    fString(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Entry
