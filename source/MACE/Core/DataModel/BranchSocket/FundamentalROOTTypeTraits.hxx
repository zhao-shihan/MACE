#pragma once

#include "RtypesCore.h"

#include <concepts>

namespace MACE::Core::DataModel::BranchSocket {

template<typename Fund_t>
concept IsROOTFundamental =
    std::same_as<std::remove_cv_t<Fund_t>, Char_t> or
    std::same_as<std::remove_cv_t<Fund_t>, UChar_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Short_t> or
    std::same_as<std::remove_cv_t<Fund_t>, UShort_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Int_t> or
    std::same_as<std::remove_cv_t<Fund_t>, UInt_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Float_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Double_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Long64_t> or
    std::same_as<std::remove_cv_t<Fund_t>, ULong64_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Long_t> or
    std::same_as<std::remove_cv_t<Fund_t>, ULong_t> or
    std::same_as<std::remove_cv_t<Fund_t>, Bool_t>;

template<IsROOTFundamental Fund_t>
consteval char GetBranchTypeName() {
    if constexpr (std::is_same_v<Fund_t, Char_t>) {
        return 'B';
    } else if constexpr (std::is_same_v<Fund_t, UChar_t>) {
        return 'b';
    } else if constexpr (std::is_same_v<Fund_t, Short_t>) {
        return 'S';
    } else if constexpr (std::is_same_v<Fund_t, UShort_t>) {
        return 's';
    } else if constexpr (std::is_same_v<Fund_t, Int_t>) {
        return 'I';
    } else if constexpr (std::is_same_v<Fund_t, UInt_t>) {
        return 'i';
    } else if constexpr (std::is_same_v<Fund_t, Float_t>) {
        return 'F';
    } else if constexpr (std::is_same_v<Fund_t, Double_t>) {
        return 'D';
    } else if constexpr (std::is_same_v<Fund_t, Long64_t>) {
        return 'L';
    } else if constexpr (std::is_same_v<Fund_t, ULong64_t>) {
        return 'l';
    } else if constexpr (std::is_same_v<Fund_t, Long_t>) {
        return 'G';
    } else if constexpr (std::is_same_v<Fund_t, ULong_t>) {
        return 'g';
    } else if constexpr (std::is_same_v<Fund_t, Bool_t>) {
        return 'O';
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
