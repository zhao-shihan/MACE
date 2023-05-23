namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, typename U>
    requires(std::integral<T> and std::integral<U>) or
                (std::floating_point<T> and std::floating_point<U>)
FundamentalEntry<AData, AUniqueID, T, U>::FundamentalEntry() :
    Base(),
    fValue(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Entry
