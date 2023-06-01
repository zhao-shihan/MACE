#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class MCP final : public DescriptionSingletonBase<MCP> {
    friend Env::Memory::SingletonFactory;

private:
    MCP();

public:
    const auto& Width() const { return fWidth; }
    const auto& Thickness() const { return fThickness; }

    void Width(double val) { fWidth = val; }
    void Thickness(double val) { fThickness = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fWidth;
    double fThickness;
};

} // namespace MACE::Detector::Description
