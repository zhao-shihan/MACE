namespace MACE::DataModel::inline BranchSocket {

template<Concept::Arithmetic T, std::size_t N>
VectorBranchSocket2<T, N>::VectorBranchSocket2(std::string name, const std::array<std::string, N>& leafNames, const std::array<T, N>& defaultValue) :
    BranchSocketBase2<VectorBranchSocket2<T, N>, std::array<T, N>>(std::move(name)),
    fLeafList(
        [&leafNames] {
            std::string leafList;
            leafList.append(leafNames[0]).append(std::string{'/', ROOTUtil::LeafTypeCode<T>()});
            for (gsl::index i = 1; i < ToSigned(N); ++i) {
                leafList.append(":").append(leafNames[i]);
            }
            return leafList;
        }()),
    fVector(defaultValue) {}

} // namespace MACE::DataModel::inline BranchSocket
