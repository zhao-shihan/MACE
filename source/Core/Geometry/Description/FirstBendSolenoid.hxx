#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class FirstBendSolenoid final : public IDescription {
public:
    static FirstBendSolenoid& Instance() noexcept;

private:
    FirstBendSolenoid();
    ~FirstBendSolenoid() noexcept = default;
    FirstBendSolenoid(const FirstBendSolenoid&) = delete;
    FirstBendSolenoid& operator=(const FirstBendSolenoid&) = delete;

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
