#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class FirstTransportSolenoid final : public IDescription {
public:
    static FirstTransportSolenoid& Instance() noexcept;

private:
    FirstTransportSolenoid() = default;
    ~FirstTransportSolenoid() noexcept = default;
    FirstTransportSolenoid(const FirstTransportSolenoid&) = delete;
    FirstTransportSolenoid& operator=(const FirstTransportSolenoid&) = delete;

public:
    std::string GetName() const override { return "FirstTransportSolenoid"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetOuterRaidus() const { return fOuterRadius; }
    const auto& GetInnerRaidus() const { return fInnerRadius; }
    const auto& GetLength() const { return fLength; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 7.5_cm;
    double fOuterRadius = 12.5_cm;
    double fLength = 20_cm;
};

} // namespace MACE::Core::Geometry::Description
