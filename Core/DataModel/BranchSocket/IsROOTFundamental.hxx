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

} // namespace MACE::Core::DataModel::BranchSocket
