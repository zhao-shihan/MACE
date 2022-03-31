#pragma once

#include "Core/Geometry/Description/CalorimeterField.hxx"

namespace MACE::Core::Geometry::Description {

class CalorimeterShield final : public IDescription {
public:
    static CalorimeterShield& Instance() noexcept;

private:
    CalorimeterShield();
    ~CalorimeterShield() noexcept = default;
    CalorimeterShield(const CalorimeterShield&) = delete;
    CalorimeterShield& operator=(const CalorimeterShield&) = delete;

public:
    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetInnerLength() const { return fInnerLength; }
    const auto& GetWindowRadius() const { return fWindowRadius; }
    const auto& GetThickness() const { return fThickness; }
    auto GetTransform() const { return CalorimeterField::Instance().GetTransform(); }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Core::Geometry::Description
