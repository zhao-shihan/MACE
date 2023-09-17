namespace MACE::DataModel::inline Column {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, std::size_t N, Concept::NumericVectorAny<N> U>
    requires(std::integral<T> and std::integral<VectorValueType<U>>) or
                (std::floating_point<T> and std::floating_point<VectorValueType<U>>)
VectorColumn<AData, AUniqueID, T, N, U>::VectorColumn() :
    Base(),
    fVector(VectorCast<U>(this->fgBranchSocket.Value())) {}

} // namespace MACE::DataModel::inline Column
