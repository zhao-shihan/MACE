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

    auto Radius() const -> const auto& { return fRadius; }
    auto Length() const -> const auto& { return fLength; }

    auto Radius(auto v) -> void { fRadius = v; }
    auto Length(auto v) -> void { fLength = v; }

    MACE_ALWAYS_INLINE auto Center() const -> muc::array3d;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    class FieldType {
        friend class EMCField;

    public:
        FieldType();

        auto UseFast() const -> auto { return fUseFast; }
        auto FastField() const -> auto { return fFastField; }
        auto FieldMap() const -> const auto& { return fFieldMap; }

        auto UseFast(bool val) -> void { fUseFast = val; }
        auto FastField(double val) -> void { fFastField = val; }
        auto FieldMap(std::string val) -> void { fFieldMap = std::move(val); }

    private:
        bool fUseFast;
        double fFastField;
        std::string fFieldMap;
    };

    auto Field() const -> const auto& { return fField; }
    auto Field() -> auto& { return fField; }

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

    FieldType fField;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/EMCField.inl"
