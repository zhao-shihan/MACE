#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class Calorimeter final : public IDescription {
public:
    static Calorimeter& Instance() noexcept;

private:
    Calorimeter();
    ~Calorimeter() noexcept = default;
    Calorimeter(const Calorimeter&) = delete;
    Calorimeter& operator=(const Calorimeter&) = delete;

public:
    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetInnerLength() const { return fInnerLength; }
    const auto& GetWindowRadius() const { return fWindowRadius; }
    const auto& GetCrystalLength() const { return fCrystalLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetCrystalLength(double val) { fCrystalLength = val; }

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fCrystalLength;
};

} // namespace MACE::Core::Geometry::Description
