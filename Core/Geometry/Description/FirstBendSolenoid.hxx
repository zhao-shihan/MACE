#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class FirstBendSolenoid final : public IDescription {
public:
    static FirstBendSolenoid& Instance() noexcept;

private:
    FirstBendSolenoid() = default;
    ~FirstBendSolenoid() noexcept = default;
    FirstBendSolenoid(const FirstBendSolenoid&) = delete;
    FirstBendSolenoid& operator=(const FirstBendSolenoid&) = delete;

public:
    std::string GetName() const override { return "FirstBendSolenoid"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetOuterRaidus() const { return fOuterRadius; }
    const auto& GetInnerRaidus() const { return fInnerRadius; }
    const auto& GetBendRadius() const { return fBendRadius; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fInnerRadius = 7.5_cm;
    double fOuterRadius = 12.5_cm;
    double fBendRadius = 50_cm;
};

} // namespace MACE::Core::Geometry::Description
