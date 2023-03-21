namespace MACE::DataModel::inline BranchSocket {

template<Concept::ROOTFundamental T>
FundamentalBranchSocket2<T>::FundamentalBranchSocket2(std::string name, T defaultValue) :
    BranchSocketBase2<FundamentalBranchSocket2<T>, T>(std::move(name)),
    fValue(defaultValue) {}

} // namespace MACE::DataModel::inline BranchSocket
