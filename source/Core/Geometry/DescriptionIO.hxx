/// @file Read/write the current geometry description configuration from/to a yaml.
/// @attention If a new geometry description class is added, it needs to be added to
/// the std::tuple in the source file. Otherwise it wouldn't be covered.
/// @author Shi-Han Zhao

#pragma once

#include <string>

namespace MACE::Core::Geometry::DescriptionIO {

/// @brief Read the current geometry description configuration from a yaml.
void Read(const std::string& yamlFileName);

/// @brief Write the current geometry description configuration to a yaml.
void Write(const std::string& yamlFileName);

} // namespace MACE::Core::Geometry::DescriptionIO
