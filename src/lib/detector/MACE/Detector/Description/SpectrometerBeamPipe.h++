#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class SpectrometerBeamPipe final : public DescriptionSingletonBase<SpectrometerBeamPipe> {
    friend Env::Memory::SingletonInstantiator;

private:
    SpectrometerBeamPipe();
    ~SpectrometerBeamPipe() = default;

public:
    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto Thickness() const -> auto { return fThickness; }
    auto Length() const -> auto { return fLength; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto Length(double val) -> void { fLength = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fThickness;
    double fLength;
};

} // namespace MACE::Detector::Description
