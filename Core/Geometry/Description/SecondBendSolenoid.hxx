#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SecondBendSolenoid final : public IDescription {
public:
    static SecondBendSolenoid& Instance() noexcept;

private:
    SecondBendSolenoid();
    ~SecondBendSolenoid() noexcept = default;
    SecondBendSolenoid(const SecondBendSolenoid&) = delete;
    SecondBendSolenoid& operator=(const SecondBendSolenoid&) = delete;

public:
    const auto& GetOuterRaidus() const { return fOuterRadius; }
    const auto& GetInnerRaidus() const { return fInnerRadius; }
    const auto& GetBendRadius() const { return fBendRadius; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fInnerRadius;
    double fOuterRadius;
    double fBendRadius;
};

} // namespace MACE::Core::Geometry::Description
