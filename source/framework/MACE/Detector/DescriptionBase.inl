namespace MACE::Detector {

template<typename AValue, typename AReadAs, std::convertible_to<std::string>... AStrings>
    requires std::assignable_from<AValue&, AReadAs>
void DescriptionBase::ImportValue(const YAML::Node& node, AValue& value, AStrings&&... nodeNames) {
    if (const auto leaf = UnpackToLeafNodeForImporting(node, nodeNames...);
        leaf.has_value()) {
        value = leaf->template as<AReadAs>();
    } else {
        PrintNodeNotFoundWarning(nodeNames...);
    }
}

template<typename AReadAs, std::convertible_to<std::string>... AStrings>
void DescriptionBase::ImportValue(const YAML::Node& node, const std::regular_invocable<AReadAs> auto& ImportAction, AStrings&&... nodeNames) {
    if (const auto leaf = UnpackToLeafNodeForImporting(node, nodeNames...);
        leaf.has_value()) {
        ImportAction(leaf->template as<AReadAs>());
    } else {
        PrintNodeNotFoundWarning(nodeNames...);
    }
}

template<typename AValue, typename AWriteAs, std::convertible_to<std::string>... AStrings>
    requires std::convertible_to<const AValue&, AWriteAs>
void DescriptionBase::ExportValue(YAML::Node& node, const AValue& value, AStrings&&... nodeNames) const {
    UnpackToLeafNodeForExporting(node, nodeNames...) = static_cast<AWriteAs>(value);
}

template<std::convertible_to<std::string>... AStrings>
std::optional<const YAML::Node> DescriptionBase::UnpackToLeafNodeForImporting(const YAML::Node& node, AStrings&&... nodeNames) {
    try {
        std::array<YAML::Node, sizeof...(nodeNames)> leafNodes;
        gsl::index i = 0;
        TupleForEach(std::tie(std::forward<AStrings>(nodeNames)...),
                     [&node, &leafNodes, &i](auto&& name) {
                         leafNodes[i] = (i == 0 ? node : leafNodes[i - 1])[name];
                         ++i;
                     });
        return leafNodes.back();
    } catch (const YAML::InvalidNode&) {
        return std::nullopt;
    }
}

template<std::convertible_to<std::string>... AStrings>
YAML::Node DescriptionBase::UnpackToLeafNodeForExporting(YAML::Node& node, AStrings&&... nodeNames) const {
    std::array<YAML::Node, sizeof...(nodeNames)> leafNodes;
    gsl::index i = 0;
    TupleForEach(std::tie(std::forward<AStrings>(nodeNames)...),
                 [&node, &leafNodes, &i](auto&& name) {
                     leafNodes[i] = (i == 0 ? node : leafNodes[i - 1])[name];
                     ++i;
                 });
    return leafNodes.back();
}

template<std::convertible_to<std::string>... AStrings>
void DescriptionBase::PrintNodeNotFoundWarning(AStrings&&... nodeNames) const {
    if (const auto& env = Env::BasicEnv::Instance();
        env.GetVerboseLevel() >= Env::VerboseLevel::Warning) {
        std::cout << "MACE::Detector::DescriptionBase: YAML node \"" << fName;
        TupleForEach(std::tie(std::forward<AStrings>(nodeNames)...),
                     [](auto&& name) {
                         std::cout << '/' << name;
                     });
        std::cout << "\" not defined, skipping" << std::endl;
    }
}

} // namespace MACE::Detector
