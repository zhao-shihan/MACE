#pragma once

#include "Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class VertexDetector final : public IDescription {
public:
    static VertexDetector& Instance() noexcept;

private:
    VertexDetector() = default;
    ~VertexDetector() noexcept = default;
    VertexDetector(const VertexDetector&) = delete;
    VertexDetector& operator=(const VertexDetector&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "VertexDetector"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetWidth() const { return fWidth; }
    [[nodiscard]] const auto& GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fWidth = 15_cm;
    double fThickness = 1_cm;
};

} // namespace MACE::Geometry::Description
