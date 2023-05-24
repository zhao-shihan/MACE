namespace MACE::DataModel::inline Field {

template<class AData, gsl::index AUniqueID, std::size_t AMaxSize, std::convertible_to<FixedString<AMaxSize>> T>
    requires std::convertible_to<FixedString<AMaxSize>, T>
StringField<AData, AUniqueID, AMaxSize, T>::StringField() :
    Base(),
    fString(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Field
