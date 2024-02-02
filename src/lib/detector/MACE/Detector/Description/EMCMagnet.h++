#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class EMCMagnet final : public DescriptionSingletonBase<EMCMagnet> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMCMagnet();
    ~EMCMagnet() noexcept = default;

public:
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto OuterRadius() const -> const auto& { return fOuterRadius; }
    auto Length() const -> const auto& { return fLength; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto OuterRadius(double val) -> void { fOuterRadius = val; }
    auto Length(double val) -> void { fLength = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
};

} // namespace MACE::Detector::Description
