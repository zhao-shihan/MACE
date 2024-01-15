namespace MACE::inline Extension::MPIX {

auto ParallelizePath(std::convertible_to<std::filesystem::path> auto&& path) -> std::filesystem::path {
    std::filesystem::path result{std::forward<decltype(path)>(path)};
    ParallelizePathInPlace(result);
    return result;
}

auto ParallelizePath(std::convertible_to<std::filesystem::path> auto&& path, std::string_view extension) -> std::filesystem::path {
    std::filesystem::path result{std::forward<decltype(path)>(path)};
    ParallelizePathInPlace(result, extension);
    return result;
}

} // namespace MACE::inline Extension::MPIX
