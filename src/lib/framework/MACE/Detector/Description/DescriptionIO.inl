namespace MACE::Detector::Description {

namespace internal {

template<std::intmax_t i, typename T>
struct FillDescriptionArray {
    constexpr void operator()(std::array<DescriptionBase*, std::tuple_size_v<T>>& descriptions) const {
        std::get<i>(descriptions) = std::addressof(std::tuple_element_t<i, T>::Instance());
    }
};

} // namespace internal

template<stdx::tuple_like T>
auto DescriptionIO::Import(const std::filesystem::path& yamlFile) -> void {
    std::array<DescriptionBase*, std::tuple_size_v<T>> descriptions;
    StaticForEach<0, descriptions.size(),
                  internal::FillDescriptionArray, T>(descriptions);
    ImportImpl(yamlFile, descriptions);
}

template<stdx::tuple_like T>
auto DescriptionIO::Export(const std::filesystem::path& yamlFile, std::string_view fileComment) -> void {
    std::array<DescriptionBase*, std::tuple_size_v<T>> descriptions;
    StaticForEach<0, descriptions.size(),
                  internal::FillDescriptionArray, T>(descriptions);
    ExportImpl(yamlFile, fileComment, descriptions);
}

template<stdx::tuple_like T>
auto DescriptionIO::Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment) -> void {
    std::array<DescriptionBase*, std::tuple_size_v<T>> descriptions;
    StaticForEach<0, descriptions.size(),
                  internal::FillDescriptionArray, T>(descriptions);
    IxportImpl(yamlFile, fileComment, descriptions);
}

template<typename... ArgsOfImport>
auto DescriptionIO::Import(const std::ranges::range auto& yamlText) -> void
    requires std::convertible_to<typename std::decay_t<decltype(yamlText)>::value_type, std::string>
{
    std::filesystem::path yamlPath;
    std::uint_fast64_t extraSuffix{};
    do {
        auto yamlName{fmt::format("{}tmpgeom{:x}{:x}",
                                  Env::BasicEnv::Instance().Argv()[0],
                                  std::chrono::steady_clock::now().time_since_epoch().count(),
                                  ++extraSuffix)};
        if (Env::MPIEnv::Initialized()) {
            yamlName.append(fmt::format(".mpi{}", Env::MPIEnv::Instance().CommWorldRank()));
        }
        yamlName.append(".yaml");
        yamlPath = std::filesystem::temp_directory_path() / yamlName;
    } while (std::filesystem::exists(yamlPath));

    const auto yamlFile{std::fopen(yamlPath.generic_string().c_str(), "w")};
    if (yamlFile == nullptr) {
        throw std::runtime_error("MACE::Detector::Description::DescriptionIO::Import: Cannot open temp yaml file");
    }
    for (auto&& line : yamlText) {
        fmt::println(yamlFile, "{}", line);
    }
    std::fclose(yamlFile);

    Import<ArgsOfImport...>(yamlPath);

    std::error_code muteRemoveError;
    std::filesystem::remove(yamlPath, muteRemoveError);
}

auto DescriptionIO::ImportImpl(const std::filesystem::path& yamlFile, std::ranges::input_range auto& descriptions) -> void {
    const auto geomYaml{YAML::LoadFile(yamlFile.generic_string())};
    for (auto&& description : std::as_const(descriptions)) {
        description->Import(geomYaml);
    }
}

auto DescriptionIO::ExportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions) -> void {
    std::vector<std::pair<std::string_view, DescriptionBase*>> sortedDescriptions;
    sortedDescriptions.reserve(descriptions.size());
    for (auto&& description : descriptions) {
        sortedDescriptions.emplace_back(description->Name(), description);
    }
    std::ranges::sort(sortedDescriptions);

    YAML::Node geomYaml;
    for (auto&& [_, description] : std::as_const(sortedDescriptions)) {
        description->Export(geomYaml);
    }

    struct InvalidFile {};
    try {
        if (yamlFile.empty()) { throw InvalidFile{}; }

        std::ofstream yamlOut;
        try {
            if (Env::MPIEnv::Available()) {
                yamlOut.open(MPIX::ParallelizePath(yamlFile), std::ios::out);
            } else {
                const auto parent{yamlFile.parent_path()};
                if (not parent.empty()) { std::filesystem::create_directories(parent); }
                yamlOut.open(yamlFile, std::ios::out);
            }
        } catch (const std::filesystem::filesystem_error&) { throw InvalidFile{}; }
        if (not yamlOut.is_open()) { throw InvalidFile{}; }

        if (not fileComment.empty()) {
            const auto firstLineFeed{fileComment.find_first_of('\n')};
            const auto begin{fileComment.begin()};
            const auto end{(firstLineFeed == std::string_view::npos) ? fileComment.end() : std::next(begin, firstLineFeed)};
            yamlOut << "# " << std::string_view(begin, end) << "\n\n";
        }
        yamlOut << geomYaml << std::endl;
    } catch (const InvalidFile&) {
        MACE_ENVIRONMENT_CONTROLLED_OUT(Error, std::cout)
            << "MACE::Detector::Description::DescriptionIO::ExportImpl: Cannot open yaml file, export failed" << std::endl;
    }
}

auto DescriptionIO::IxportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions) -> void {
    ExportImpl(std::filesystem::path(yamlFile).replace_extension(".prev.yaml"), fileComment, descriptions);
    ImportImpl(yamlFile, descriptions);
    ExportImpl(std::filesystem::path(yamlFile).replace_extension(".curr.yaml"), fileComment, descriptions);
}

} // namespace MACE::Detector::Description
