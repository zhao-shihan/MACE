#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Math/GetDigits.h++"
#include "MACE/Extension/stdx/to_signed.h++"

#include "backward.hpp"

#include <climits>
#include <iostream>

namespace MACE::inline Utility {

template<Concept::Character AChar = char>
void PrintStackTrace(backward::StackTrace& stack, std::basic_ostream<AChar>& os = std::clog);

} // namespace MACE::inline Utility

#include "MACE/Utility/PrintStackTrace.inl"
