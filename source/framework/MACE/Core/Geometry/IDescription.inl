namespace MACE::Core::Geometry {

template<typename AValue, typename AReadAs> // clang-format off
    requires std::assignable_from<AValue&, AReadAs>
void IDescription::ReadValueNode(const YAML::Node& node, const std::string& valueName, AValue& value) { // clang-format on
    if (const auto valueNode = node[valueName];
        valueNode.IsDefined()) {
        value = valueNode.as<AReadAs>();
    } else {
        std::cout << "Node <" << fName << "::" << valueName << "> not defined, skipping." << std::endl;
    }
}

template<typename AReadAs>
void IDescription::ReadValueNode(const YAML::Node& node, const std::string& valueName, const std::regular_invocable<AReadAs> auto& ReadAction) {
    if (const auto valueNode = node[valueName];
        valueNode.IsDefined()) {
        ReadAction(valueNode.as<AReadAs>());
    } else {
        std::cout << "Node <" << fName << "::" << valueName << "> not defined, skipping." << std::endl;
    }
}

} // namespace MACE::Core::Geometry
