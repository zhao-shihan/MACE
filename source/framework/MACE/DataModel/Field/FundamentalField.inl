namespace MACE::DataModel::inline Field {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, typename U>
    requires(std::integral<T> and std::integral<U>) or
                (std::floating_point<T> and std::floating_point<U>)
FundamentalField<AData, AUniqueID, T, U>::FundamentalField() :
    Base(),
    fValue(this->fgBranchSocket.Value()) {}

} // namespace MACE::DataModel::inline Field
