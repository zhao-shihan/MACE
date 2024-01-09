namespace MACE::inline Extension::MPIX {

auto MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path) -> std::filesystem::path {
    std::filesystem::path result{std::forward<decltype(path)>(path)};
    MakeMPIFilePathInPlace(result);
    return result;
}

auto MakeMPIFilePath(std::convertible_to<std::filesystem::path> auto&& path, std::string_view extension) -> std::filesystem::path {
    std::filesystem::path result{std::forward<decltype(path)>(path)};
    MakeMPIFilePathInPlace(result, extension);
    return result;
}

} // namespace MACE::inline Extension::MPIX
