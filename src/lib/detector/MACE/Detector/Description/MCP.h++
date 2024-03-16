#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class MCP final : public DescriptionSingletonBase<MCP> {
    friend Env::Memory::SingletonInstantiator;

private:
    MCP();
    ~MCP() = default;

public:
    auto Diameter() const -> auto { return fDiameter; }
    auto Thickness() const -> auto { return fThickness; }
    auto AnodeDistance() const -> auto { return fAnodeDistance; }
    auto AnodeThickness() const -> auto { return fAnodeThickness; }

    auto Diameter(double val) -> void { fDiameter = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto AnodeDistance(double val) -> void { fAnodeDistance = val; }
    auto AnodeThickness(double val) -> void { fAnodeThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fDiameter;
    double fThickness;
    double fAnodeDistance;
    double fAnodeThickness;
};

} // namespace MACE::Detector::Description
