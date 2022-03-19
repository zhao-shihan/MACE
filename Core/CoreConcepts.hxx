#pragma once

#include <concepts>

#include "RtypesCore.h"

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension.
    // inline namespace Core {

    namespace DataModel {

        template<typename Fund_t>
        concept FundamentalType =
            std::same_as<Fund_t, Char_t> or
            std::same_as<Fund_t, UChar_t> or
            std::same_as<Fund_t, Short_t> or
            std::same_as<Fund_t, UShort_t> or
            std::same_as<Fund_t, Int_t> or
            std::same_as<Fund_t, UInt_t> or
            std::same_as<Fund_t, Float_t> or
            std::same_as<Fund_t, Double_t> or
            std::same_as<Fund_t, Long64_t> or
            std::same_as<Fund_t, ULong64_t> or
            std::same_as<Fund_t, Long_t> or
            std::same_as<Fund_t, ULong_t> or
            std::same_as<Fund_t, Bool_t>;

        template<typename Class_t>
        concept ClassType = std::is_class_v<Class_t>;

    }

}
