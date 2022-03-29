#pragma once

#include "Core/Geometry/Description/FirstBendField.hxx"

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
    std::string GetName() const override { return "SecondTransportField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return "As this GetTranslation()"; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetLength() const { return fLength; }
    const auto& GetRadius() const { return FirstBendField::Instance().GetRadius(); }
    G4Transform3D GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 100_cm;
};

} // namespace MACE::Geometry::Description
