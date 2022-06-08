#include <iostream>

namespace MACE::Core::Geometry {

template<typename ValueT, typename ReadAsT>
void IDescription::ReadValueNode(const YAML::Node& node, const char* valueName, ValueT& value) {
    const auto valueNode = node[valueName];
    if (valueNode.IsDefined()) {
        value = valueNode.as<ReadAsT>();
    } else {
        std::cout << "Node <" << fName << "::" << valueName << "> not defined, skipping." << std::endl;
    }
}

template<typename ValueT, typename WriteAsT>
void IDescription::WriteValueNode(YAML::Node& node, const char* valueName, const ValueT& value) const {
    if constexpr (std::same_as<ValueT, WriteAsT>) {
        node[valueName] = value;
    } else {
        node[valueName] = WriteAsT(value);
    }
}

} // namespace MACE::Core::Geometry
