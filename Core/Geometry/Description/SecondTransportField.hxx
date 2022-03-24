#pragma once

#include "Geometry/Description/FirstBendField.hxx"

namespace MACE::Geometry::Description {

class SecondTransportField final : public IDescription {
public:
    static SecondTransportField& Instance() noexcept;

private:
    SecondTransportField() = default;
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "SecondTransportField"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "As this GetTranslation()"; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetRadius() const { return FirstBendField::Instance().GetRadius(); }
    [[nodiscard]] G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 100_cm;
};

} // namespace MACE::Geometry::Description
