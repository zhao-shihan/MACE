#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class World final : public IDescription {
public:
    static World& Instance() noexcept;

private:
    World() = default;
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "World"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return "The geometry world."; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return "Vacuum (of air). A properly defined pressure/density is recommended."; }
    [[nodiscard]] std::string GetShapeDescription() const override { return "A big box that can contain everything."; }
    [[nodiscard]] std::string GetMotherDescription() const override { return "Void."; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription() const override { return "No rotation."; }

    [[nodiscard]] const auto& GetHalfXExtent() const { return fHalfXExtent; }
    [[nodiscard]] const auto& GetHalfYExtent() const { return fHalfYExtent; }
    [[nodiscard]] const auto& GetHalfZExtent() const { return fHalfZExtent; }

    void SetHalfXExtent(double val) { fHalfXExtent = val; }
    void SetHalfYExtent(double val) { fHalfYExtent = val; }
    void SetHalfZExtent(double val) { fHalfZExtent = val; }

private:
    double fHalfXExtent = 3_m;
    double fHalfYExtent = 1_m;
    double fHalfZExtent = 4_m;
};

} // namespace MACE::Geometry::Description
