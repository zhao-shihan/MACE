namespace MACE::Core::Geometry {

namespace Internal {

template<std::intmax_t i, class ADescriptionTuple>
struct FillDescriptionArray {
    constexpr void operator()(auto& descriptions) const {
        std::get<i>(descriptions) = std::addressof(std::tuple_element_t<i, ADescriptionTuple>::Instance());
    }
};

} // namespace Internal

template<InstantiatedFrom<std::tuple> ADescriptionTuple>
void DescriptionIO::Import(const std::string& yamlFileName) {
    std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>> descriptionArray;
    Utility::StaticForEach<
        0, descriptionArray.size(), Internal::FillDescriptionArray,
        decltype(std::tie(descriptionArray)), ADescriptionTuple>(std::tie(descriptionArray));
    ImportImpl(yamlFileName, descriptionArray);
}

template<InstantiatedFrom<std::tuple> ADescriptionTuple>
void DescriptionIO::Export(const std::string& yamlFileName, const std::string& fileComment) {
    std::array<ObserverPtr<IDescription>, std::tuple_size_v<ADescriptionTuple>> descriptionArray;
    Utility::StaticForEach<
        0, descriptionArray.size(), Internal::FillDescriptionArray,
        decltype(std::tie(descriptionArray)), ADescriptionTuple>(std::tie(descriptionArray));
    ExportImpl(yamlFileName, fileComment, descriptionArray);
}

void DescriptionIO::ImportImpl(const std::string& yamlFileName, std::ranges::range auto& descriptions) {
    const auto geomYaml = YAML::LoadFile(yamlFileName);
    for (auto&& description : std::as_const(descriptions)) {
        description->Import(geomYaml);
    }
}

void DescriptionIO::ExportImpl(const std::string& yamlFileName, std::string fileComment, const std::ranges::sized_range auto& descriptions) {
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

    std::ofstream yamlOut(yamlFileName, std::ios::out);
    if (not fileComment.empty()) {
        const auto firstLineFeed = fileComment.find_first_of('\n');
        const auto begin = fileComment.cbegin();
        const auto end = (firstLineFeed == std::string::npos) ? fileComment.cend() : std::next(begin, firstLineFeed);
        yamlOut << "# " << std::string_view(begin, end) << "\n\n";
    }
    yamlOut << geomYaml << std::endl;
    yamlOut.close();
}

} // namespace MACE::Core::Geometry
