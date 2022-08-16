namespace MACE::Core::Geometry {

namespace internal {

template<std::intmax_t i, class ADescriptionTuple>
struct FillDescriptionArray {
    constexpr void operator()(std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>>& descriptions) const {
        std::get<i>(descriptions) = std::addressof(std::tuple_element_t<i, ADescriptionTuple>::Instance());
    }
};

} // namespace internal

template<InstantiatedFrom<std::tuple> ADescriptionTuple>
void DescriptionIO::Import(const std::filesystem::path& yamlFile) {
    std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>> descriptions;
    Utility::StaticForEach<0, descriptions.size(),
                           internal::FillDescriptionArray, ADescriptionTuple>(descriptions);
    ImportImpl(yamlFile, descriptions);
}

template<InstantiatedFrom<std::tuple> ADescriptionTuple>
void DescriptionIO::Export(const std::filesystem::path& yamlFile, const std::string& fileComment) {
    std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>> descriptions;
    Utility::StaticForEach<0, descriptions.size(),
                           internal::FillDescriptionArray, ADescriptionTuple>(descriptions);
    ExportImpl(yamlFile, fileComment, descriptions);
}

template<InstantiatedFrom<std::tuple> ADescriptionTuple>
void DescriptionIO::Ixport(const std::filesystem::path& yamlFile, const std::string& fileComment) {
    std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>> descriptions;
    Utility::StaticForEach<0, descriptions.size(),
                           internal::FillDescriptionArray, ADescriptionTuple>(descriptions);
    IxportImpl(yamlFile, fileComment, descriptions);
}

template<typename... ArgsOfImport>
void DescriptionIO::Import(const InstantiatedFrom<std::tuple> auto& yamlText) {
    auto yamlPath = std::filesystem::temp_directory_path() / "tmp_mace_geom.yaml";
    if (Environment::MPIEnvironment::Available()) {
        Utility::MPIUtil::MakeMPIFilePathInPlace(yamlPath);
    }
    yamlPath.concat(std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

    std::fstream yamlOut(yamlPath, std::ios::out);
    if (yamlOut.is_open()) {
        Utility::TupleForEach(yamlText,
                              [&yamlOut](const auto& line) {
                                  yamlOut << line << '\n';
                              });
        yamlOut << std::endl;
        yamlOut.close();
        Import<ArgsOfImport...>(yamlPath);
    } else {
        throw std::runtime_error("MACE::Core::Geometry::DescriptionIO::Import: Cannot open temp yaml file");
    }

    std::error_code muteRemoveError;
    std::filesystem::remove(yamlPath, muteRemoveError);
}

void DescriptionIO::ImportImpl(const std::filesystem::path& yamlFile, std::ranges::range auto& descriptions) {
    const auto geomYaml = YAML::LoadFile(yamlFile);
    for (auto&& description : std::as_const(descriptions)) {
        description->Import(geomYaml);
    }
}

void DescriptionIO::ExportImpl(const std::filesystem::path& yamlFile, std::string fileComment, const std::ranges::range auto& descriptions) {
    std::vector<std::pair<std::string_view, ObserverPtr<IDescription>>> sortedDescriptions;
    sortedDescriptions.reserve(descriptions.size());
    for (auto&& description : descriptions) {
        sortedDescriptions.emplace_back(description->GetName(), description);
    }
    std::ranges::sort(sortedDescriptions);

    YAML::Node geomYaml;
    for (auto&& [_, description] : std::as_const(sortedDescriptions)) {
        description->Export(geomYaml);
    }

    struct InvalidFile {};
    try {
        if (yamlFile.empty()) { throw InvalidFile(); }

        std::ofstream yamlOut;
        try {
            if (Environment::MPIEnvironment::Available()) {
                yamlOut.open(Utility::MPIUtil::MakeMPIFilePath(yamlFile), std::ios::out);
            } else {
                const auto parent = yamlFile.parent_path();
                if (not parent.empty()) { std::filesystem::create_directories(parent); }
                yamlOut.open(yamlFile, std::ios::out);
            }
        } catch (const std::filesystem::filesystem_error&) { throw InvalidFile(); }
        if (not yamlOut.is_open()) { throw InvalidFile(); }

        if (not fileComment.empty()) {
            const auto firstLineFeed = fileComment.find_first_of('\n');
            const auto begin = fileComment.cbegin();
            const auto end = (firstLineFeed == std::string::npos) ? fileComment.cend() : std::next(begin, firstLineFeed);
            yamlOut << "# " << std::string_view(begin, end) << "\n\n";
        }
        yamlOut << geomYaml << std::endl;
        yamlOut.close();
    } catch (const InvalidFile&) {
        MACE_ENVIRONMENT_CONTROLLED_OUT(Error, std::cout)
            << "MACE::Core::Geometry::DescriptionIO::ExportImpl: Cannot open yaml file, export failed" << std::endl;
    }
}

void DescriptionIO::IxportImpl(const std::filesystem::path& yamlFile, std::string fileComment, const std::ranges::range auto& descriptions) {
    ImportImpl(yamlFile, descriptions);
    ExportImpl(std::filesystem::path(yamlFile).replace_extension(".out.yaml"), fileComment, descriptions);
}

} // namespace MACE::Core::Geometry
