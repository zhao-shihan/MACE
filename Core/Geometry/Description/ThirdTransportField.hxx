#pragma once

#include "Core/Geometry/Description/SecondBendField.hxx"

namespace MACE::Geometry::Description {

class ThirdTransportField final : public IDescription {
public:
    static ThirdTransportField& Instance() noexcept;

private:
    ThirdTransportField() = default;
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

public:
    std::string GetName() const override { return "ThirdTransportField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetLength() const { return fLength; }
    const auto& GetRadius() const { return SecondBendField::Instance().GetRadius(); }
    G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 20_cm;
};

} // namespace MACE::Geometry::Description
