#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/GetDigits10.hxx"

#include "backward.hpp"

#include <climits>
#include <iostream>
#include <string_view>

namespace MACE::Utility {

template<Concept::Character AChar = char>
void PrintStackTrace(backward::StackTrace& stack, std::basic_ostream<AChar>& os = std::clog);

} // namespace MACE::Utility

#include "MACE/Utility/PrintStackTrace.inl"
