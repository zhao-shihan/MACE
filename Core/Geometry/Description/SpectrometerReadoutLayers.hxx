#pragma once

#include "Core/Geometry/IDescription.hxx"

#include <tuple>
#include <vector>

namespace MACE::Geometry::Description {

class SpectrometerReadoutLayers final : public IDescription {
public:
    static SpectrometerReadoutLayers& Instance() noexcept;

private:
    SpectrometerReadoutLayers() = default;
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "SpectrometerReadoutLayer"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return "Readout layer of MWDC. Mother volume of cells and field wires."; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return "Helium based gas."; }
    [[nodiscard]] std::string GetShapeDescription() const override { return "Tube."; }
    [[nodiscard]] std::string GetMotherDescription() const override { return "SpectrometerBody"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription() const override { return "No rotation."; }

    [[nodiscard]] const auto& GetAllowedDistortion() const { return fAllowedDistortion; }
    /// @return Layer's information list. Subscript with layerID and get [ layer center radius, thickness(=cellWidth), length/2, nCells ].
    /// @warning This method constructs a std::vector<std::tuple<...>> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<std::tuple<...>> like this for many times could lead to performance problem.
    [[nodiscard]] std::vector<std::tuple<double, double, double, int>> GetInformationList() const;

    void SetMeanCellWidth(double val) { fCellWidth = val; }
    void SetAllowedDistortion(double val) { fAllowedDistortion = val; }

private:
    double fCellWidth = 16.2_mm;
    double fAllowedDistortion = 0.1;
};

} // namespace MACE::Geometry::Description
