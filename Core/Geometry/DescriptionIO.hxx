#pragma once

#include <string>

namespace MACE::Core::Geometry::DescriptionIO {

bool Read(const std::string& yamlFile);
bool Write(const std::string& yamlFile);

} // namespace MACE::Core::Geometry::DescriptionIO
