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
    auto BerylliumLength() const -> auto { return fBerylliumLength; }
    auto BerylliumThickness() const -> auto { return fBerylliumThickness; }
    auto AluminiumThickness() const -> auto { return fAluminiumThickness; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto BerylliumLength(double val) -> void { fBerylliumLength = val; }
    auto BerylliumThickness(double val) -> void { fBerylliumThickness = val; }
    auto AluminiumThickness(double val) -> void { fAluminiumThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fBerylliumLength;
    double fBerylliumThickness;
    double fAluminiumThickness;
};

} // namespace MACE::Detector::Description
