namespace MACE::Utility::MPIUtil {

template<size_t MaxLength_v>
std::pair<std::array<char, MaxLength_v>, int> MPIGetProcessorName() {
    std::pair<std::array<char, MaxLength_v>, int> result;
    MPI_Get_processor_name(result.first.data(), &result.second);
    return result;
}

} // namespace MACE::Utility::MPIUtil
