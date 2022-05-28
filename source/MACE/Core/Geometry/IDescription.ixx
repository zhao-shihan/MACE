#include <iostream>

namespace MACE::Core::Geometry {

template<typename Value_t, typename ReadAs_t>
void IDescription::ReadValueNode(const YAML::Node& node, const char* valueName, Value_t& value) {
    const auto valueNode = node[valueName];
    if (valueNode.IsDefined()) {
        value = valueNode.as<ReadAs_t>();
    } else {
        std::cout << "Node <" << fName << "::" << valueName << "> not defined, skipping." << std::endl;
    }
}

template<typename Value_t, typename WriteAs_t>
void IDescription::WriteValueNode(YAML::Node& node, const char* valueName, const Value_t& value) const {
    if constexpr (std::same_as<Value_t, WriteAs_t>) {
        node[valueName] = value;
    } else {
        node[valueName] = WriteAs_t(value);
    }
}

} // namespace MACE::Core::Geometry
