#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class EMCMagnet final : public DescriptionBase<EMCMagnet> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMCMagnet();
    ~EMCMagnet() = default;

public:
    // Geometry

    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto OuterRadius() const -> const auto& { return fOuterRadius; }
    auto Length() const -> const auto& { return fLength; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto OuterRadius(double val) -> void { fOuterRadius = val; }
    auto Length(double val) -> void { fLength = val; }

    // Material

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) { fMaterialName = std::move(val); }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fInnerRadius;
    double fOuterRadius;
    double fLength;

    // Material

    std::string fMaterialName;
};

} // namespace MACE::Detector::Description
