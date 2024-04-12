#pragma once

#include "MACE/Env/Memory/Singletonified.h++"

#include <concepts>

namespace MACE::Detector::Description {

template<typename... Ts>
    requires(sizeof...(Ts) <= 1)
class DescriptionBase;

template<typename T>
concept Description =
    requires {
        requires std::derived_from<T, DescriptionBase<>>;
        requires std::derived_from<T, DescriptionBase<T>>;
        requires Env::Memory::Singletonified<T>;
    };

} // namespace MACE::Detector::Description
