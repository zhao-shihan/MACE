#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class BeamDegrader final : public DescriptionSingletonBase<BeamDegrader> {
    friend Env::Memory::SingletonInstantiator;

private:
    BeamDegrader();
    ~BeamDegrader() = default;

public:
    auto Enabled() const -> auto { return fEnabled; }
    auto Width() const -> auto { return fWidth; }
    auto Thickness() const -> auto { return fThickness; }
    auto DistanceToTarget() const -> auto { return fDistanceToTarget; }

    auto Enabled(bool val) -> void { fEnabled = val; }
    auto Width(double val) -> void { fWidth = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto DistanceToTarget(double val) -> void { fDistanceToTarget = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    bool fEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTarget;
};

} // namespace MACE::Detector::Description
