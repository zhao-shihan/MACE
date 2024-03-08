#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class MCPChamber final : public DescriptionSingletonBase<MCPChamber> {
    friend Env::Memory::SingletonInstantiator;

private:
    MCPChamber();
    ~MCPChamber() = default;

public:
    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto Thickness() const -> auto { return fThickness; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto Thickness(double val) -> void { fThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fThickness;
};

} // namespace MACE::Detector::Description
