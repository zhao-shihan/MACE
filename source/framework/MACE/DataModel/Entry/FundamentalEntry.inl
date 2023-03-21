namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index BranchIndex, Concept::ROOTFundamental T, typename U>
    requires std::convertible_to<const T&, U> and std::assignable_from<T&, const U&>
FundamentalEntry<AData, BranchIndex, T, U>::FundamentalEntry() :
    Base(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Entry
