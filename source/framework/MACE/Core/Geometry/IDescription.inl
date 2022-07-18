#include <iostream>

namespace MACE::Core::Geometry {

template<typename AValue, typename AReadAs>
void IDescription::ReadValueNode(const YAML::Node& node, const char* valueName, AValue& value) {
    const auto valueNode = node[valueName];
    if (valueNode.IsDefined()) {
        value = valueNode.as<AReadAs>();
    } else {
        std::cout << "Node <" << fName << "::" << valueName << "> not defined, skipping." << std::endl;
    }
}

template<typename AValue, typename AWriteAs>
void IDescription::WriteValueNode(YAML::Node& node, const char* valueName, const AValue& value) const {
    node[valueName] = AWriteAs(value);
}

} // namespace MACE::Core::Geometry
