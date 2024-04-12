#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class SolenoidShield final : public DescriptionBase<SolenoidShield> {
    friend Env::Memory::SingletonInstantiator;

private:
    SolenoidShield();
    ~SolenoidShield() = default;

public:
    // Geometry

    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto OuterRadius() const -> auto { return fOuterRadius; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto OuterRadius(double val) -> void { fOuterRadius = val; }

    // Material

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) -> void { fMaterialName = std::move(val); }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fInnerRadius;
    double fOuterRadius;

    // Material

    std::string fMaterialName;
};

} // namespace MACE::Detector::Description
