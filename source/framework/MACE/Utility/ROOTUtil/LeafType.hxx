#pragma once

#include "MACE/Concept/ROOTFundamental.hxx"

#include "RtypesCore.h"

#include <concepts>
#include <string>
#include <type_traits>

namespace MACE::Utility::ROOTUtil {

template<Concept::ROOTFundamental T>
struct LeafType {
    LeafType() = delete;
    static constexpr char Code();
    static auto Suffix() { return std::string{'/', Code()}; }
};

} // namespace MACE::Utility::ROOTUtil

#include "MACE/Utility/ROOTUtil/LeafType.inl"
