#include "Core/Geometry/Description/SelectorField.hxx"

using MACE::Geometry::Description::SelectorField;

SelectorField& SelectorField::Instance() noexcept {
    static SelectorField instance;
    return instance;
}
