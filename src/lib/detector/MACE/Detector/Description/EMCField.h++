#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/InlineMacro.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include "CLHEP/Geometry/Transform3D.h"

#include "muc/array"

#include <utility>

namespace MACE::Detector::Description {

class EMCField final : public DescriptionBase<EMCField> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMCField();
    ~EMCField() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto Radius() const -> auto { return fRadius; }
    auto Length() const -> auto { return fLength; }

    auto Radius(double v) -> void { fRadius = v; }
    auto Length(double v) -> void { fLength = v; }

    MACE_ALWAYS_INLINE auto Center() const -> muc::array3d;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    auto FastField() const -> auto { return fFastField; }

    auto FastField(double val) -> void { fFastField = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fRadius;
    double fLength;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fFastField;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/EMCField.inl"
