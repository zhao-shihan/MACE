namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index ABranchID, Concept::ROOTFundamental T, typename U>
    requires(std::integral<T> and std::integral<U>) or
                (std::floating_point<T> and std::floating_point<U>)
FundamentalEntry<AData, ABranchID, T, U>::FundamentalEntry() :
    Base(),
    fValue(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Entry
