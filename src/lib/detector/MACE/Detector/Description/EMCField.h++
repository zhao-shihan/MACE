#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/InlineMacro.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class EMCField final : public DescriptionSingletonBase<EMCField> {
    friend Env::Memory::SingletonFactory;

private:
    EMCField();
    ~EMCField() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto Radius() const -> const auto& { return fRadius; }
    auto Length() const -> const auto& { return fLength; }

    auto Radius(auto v) -> void { fRadius = v; }
    auto Length(auto v) -> void { fLength = v; }

    MACE_ALWAYS_INLINE auto Center() const -> stdx::array3d;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    auto MagneticFluxDensity() const -> const auto& { return fMagneticFluxDensity; }

    auto MagneticFluxDensity(auto v) -> void { fMagneticFluxDensity = v; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fRadius;
    double fLength;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fMagneticFluxDensity;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/EMCField.inl"
