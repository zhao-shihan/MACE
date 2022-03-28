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
    [[nodiscard]] std::string GetName() const override { return "ThirdTransportField"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetRadius() const { return SecondBendField::Instance().GetRadius(); }
    [[nodiscard]] G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 20_cm;
};

} // namespace MACE::Geometry::Description
