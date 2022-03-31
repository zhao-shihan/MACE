#include "Core/Geometry/Description/SelectorField.hxx"

using MACE::Core::Geometry::Description::SelectorField;

SelectorField& SelectorField::Instance() noexcept {
    static SelectorField instance;
    return instance;
}
