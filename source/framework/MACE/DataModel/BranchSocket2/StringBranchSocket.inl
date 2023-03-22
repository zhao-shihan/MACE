namespace MACE::DataModel::inline BranchSocket {

template<std::size_t AMaxSize>
StringBranchSocket<AMaxSize>::StringBranchSocket(std::string name, FixedString<AMaxSize> defaultString) :
    BranchSocketBase2<StringBranchSocket<AMaxSize>, ShortString>(std::move(name)),
    fLeafName(this->fName + "/C"),
    fString(std::move(defaultString)) {}

} // namespace MACE::DataModel::inline BranchSocket
