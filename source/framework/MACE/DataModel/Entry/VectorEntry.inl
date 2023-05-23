namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, std::size_t N, Concept::NumericVectorAny<N> U>
    requires(std::integral<T> and std::integral<VectorValueType<U>>) or
                (std::floating_point<T> and std::floating_point<VectorValueType<U>>)
VectorEntry<AData, AUniqueID, T, N, U>::VectorEntry() :
    Base(),
    fVector(VectorCast<U>(this->fgBranchSocket.Value())) {}

} // namespace MACE::DataModel::inline Entry
