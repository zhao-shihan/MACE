namespace MACE::DataModel::inline BranchSocket {

template<std::size_t AMaxSize>
StringBranchSocket<AMaxSize>::StringBranchSocket(std::string name, std::string title, FixedString<AMaxSize> defaultString) :
    BranchSocketBase2<StringBranchSocket<AMaxSize>, String15>(std::move(name), std::move(title)),
    fLeafName(this->fName + "/C"),
    fString(std::move(defaultString)) {}

} // namespace MACE::DataModel::inline BranchSocket
