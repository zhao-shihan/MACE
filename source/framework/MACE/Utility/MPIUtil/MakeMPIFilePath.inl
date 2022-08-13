namespace MACE::Utility::MPIUtil {

std::filesystem::path MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path) {
    std::filesystem::path result(std::forward<decltype(path)>(path));
    MakeMPIFilePathInPlace(result);
    return result;
}

std::filesystem::path MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path, std::string_view extension) {
    std::filesystem::path result(std::forward<decltype(path)>(path));
    MakeMPIFilePathInPlace(result, extension);
    return result;
}

} // namespace MACE::Utility::MPIUtil
