#pragma once

#include "RtypesCore.h"

#include <concepts>

namespace MACE::Core::DataModel::BranchSocket {

template<typename T>
concept ROOTFundamental =
    std::same_as<T, Char_t> or
    std::same_as<T, UChar_t> or
    std::same_as<T, Short_t> or
    std::same_as<T, UShort_t> or
    std::same_as<T, Int_t> or
    std::same_as<T, UInt_t> or
    std::same_as<T, Float_t> or
    std::same_as<T, Double_t> or
    std::same_as<T, Long64_t> or
    std::same_as<T, ULong64_t> or
    std::same_as<T, Long_t> or
    std::same_as<T, ULong_t> or
    std::same_as<T, Bool_t>;

template<ROOTFundamental T>
consteval char LeafTypeCode() {
    if constexpr (std::same_as<T, Char_t>) {
        return 'B';
    } else if constexpr (std::same_as<T, UChar_t>) {
        return 'b';
    } else if constexpr (std::same_as<T, Short_t>) {
        return 'S';
    } else if constexpr (std::same_as<T, UShort_t>) {
        return 's';
    } else if constexpr (std::same_as<T, Int_t>) {
        return 'I';
    } else if constexpr (std::same_as<T, UInt_t>) {
        return 'i';
    } else if constexpr (std::same_as<T, Float_t>) {
        return 'F';
    } else if constexpr (std::same_as<T, Double_t>) {
        return 'D';
    } else if constexpr (std::same_as<T, Long64_t>) {
        return 'L';
    } else if constexpr (std::same_as<T, ULong64_t>) {
        return 'l';
    } else if constexpr (std::same_as<T, Long_t>) {
        return 'G';
    } else if constexpr (std::same_as<T, ULong_t>) {
        return 'g';
    } else if constexpr (std::same_as<T, Bool_t>) {
        return 'O';
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
