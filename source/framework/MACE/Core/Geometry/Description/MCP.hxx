#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class MCP final : public ISingletonDescription<MCP> {
    friend Env::Memory::SingletonFactory;

private:
    MCP();
    ~MCP() noexcept = default;
    MCP(const MCP&) = delete;
    MCP& operator=(const MCP&) = delete;

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

} // namespace MACE::Core::Geometry::Description
