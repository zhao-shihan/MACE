#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class EMCal final : public ISingletonDescription<EMCal> {
    friend Environment::Resource::SingletonFactory;

private:
    EMCal();
    ~EMCal() noexcept = default;
    EMCal(const EMCal&) = delete;
    EMCal& operator=(const EMCal&) = delete;

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
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fCrystalLength;
};

} // namespace MACE::Core::Geometry::Description
