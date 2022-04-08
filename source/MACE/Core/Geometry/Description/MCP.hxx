#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class MCP final : public IDescription {
public:
    static MCP& Instance() noexcept;

private:
    MCP();
    ~MCP() noexcept = default;
    MCP(const MCP&) = delete;
    MCP& operator=(const MCP&) = delete;

public:
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    double fWidth;
    double fThickness;
};

} // namespace MACE::Core::Geometry::Description
