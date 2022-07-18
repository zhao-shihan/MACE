#pragma once

#include "RtypesCore.h"

#include <concepts>

namespace MACE::Core::DataModel::BranchSocket {

template<typename AROOTFundamental>
concept IsROOTFundamental =
    std::same_as<std::remove_cv_t<AROOTFundamental>, Char_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, UChar_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Short_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, UShort_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Int_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, UInt_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Float_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Double_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Long64_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, ULong64_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Long_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, ULong_t> or
    std::same_as<std::remove_cv_t<AROOTFundamental>, Bool_t>;

template<IsROOTFundamental AROOTFundamental>
consteval char GetBranchTypeName() {
    if constexpr (std::is_same_v<AROOTFundamental, Char_t>) {
        return 'B';
    } else if constexpr (std::is_same_v<AROOTFundamental, UChar_t>) {
        return 'b';
    } else if constexpr (std::is_same_v<AROOTFundamental, Short_t>) {
        return 'S';
    } else if constexpr (std::is_same_v<AROOTFundamental, UShort_t>) {
        return 's';
    } else if constexpr (std::is_same_v<AROOTFundamental, Int_t>) {
        return 'I';
    } else if constexpr (std::is_same_v<AROOTFundamental, UInt_t>) {
        return 'i';
    } else if constexpr (std::is_same_v<AROOTFundamental, Float_t>) {
        return 'F';
    } else if constexpr (std::is_same_v<AROOTFundamental, Double_t>) {
        return 'D';
    } else if constexpr (std::is_same_v<AROOTFundamental, Long64_t>) {
        return 'L';
    } else if constexpr (std::is_same_v<AROOTFundamental, ULong64_t>) {
        return 'l';
    } else if constexpr (std::is_same_v<AROOTFundamental, Long_t>) {
        return 'G';
    } else if constexpr (std::is_same_v<AROOTFundamental, ULong_t>) {
        return 'g';
    } else if constexpr (std::is_same_v<AROOTFundamental, Bool_t>) {
        return 'O';
    }
}

} // namespace MACE::Core::DataModel::BranchSocket
