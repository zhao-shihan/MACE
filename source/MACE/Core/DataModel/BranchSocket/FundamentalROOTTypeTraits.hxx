#pragma once

#include "RtypesCore.h"

#include <concepts>

namespace MACE::Core::DataModel::BranchSocket {

template<typename ROOTFundamentalT>
concept IsROOTFundamental =
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Char_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, UChar_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Short_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, UShort_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Int_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, UInt_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Float_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Double_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Long64_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, ULong64_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Long_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, ULong_t> or
    std::same_as<std::remove_cv_t<ROOTFundamentalT>, Bool_t>;

template<IsROOTFundamental ROOTFundamentalT>
consteval char GetBranchTypeName() {
    if constexpr (std::is_same_v<ROOTFundamentalT, Char_t>) {
        return 'B';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, UChar_t>) {
        return 'b';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Short_t>) {
        return 'S';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, UShort_t>) {
        return 's';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Int_t>) {
        return 'I';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, UInt_t>) {
        return 'i';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Float_t>) {
        return 'F';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Double_t>) {
        return 'D';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Long64_t>) {
        return 'L';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, ULong64_t>) {
        return 'l';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Long_t>) {
        return 'G';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, ULong_t>) {
        return 'g';
    } else if constexpr (std::is_same_v<ROOTFundamentalT, Bool_t>) {
        return 'O';
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
