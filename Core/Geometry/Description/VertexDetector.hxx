#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class VertexDetector final : public IDescription {
public:
    static VertexDetector& Instance() noexcept;

private:
    VertexDetector() = default;
    ~VertexDetector() noexcept = default;
    VertexDetector(const VertexDetector&) = delete;
    VertexDetector& operator=(const VertexDetector&) = delete;

public:
    std::string GetName() const override { return "VertexDetector"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fWidth = 15_cm;
    double fThickness = 1_cm;
};

} // namespace MACE::Core::Geometry::Description
