#pragma once

#include "Core/Geometry/IDescription.hxx"

#include <tuple>
#include <vector>

namespace MACE::Core::Geometry::Description {

class SpectrometerReadoutLayers final : public IDescription {
public:
    static SpectrometerReadoutLayers& Instance() noexcept;

private:
    SpectrometerReadoutLayers();
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

public:
    const auto& GetAllowedDistortion() const { return fAllowedDistortion; }
    /// @return Layer's information list. Subscript with layerID and get [ layer center radius, thickness(=cellWidth), length/2, nCells ].
    /// @warning This method constructs a std::vector<std::tuple<...>> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<std::tuple<...>> like this for many times could lead to performance problem.
    std::vector<std::tuple<double, double, double, int>> GetInformationList() const;

    void SetMeanCellWidth(double val) { fCellWidth = val; }
    void SetAllowedDistortion(double val) { fAllowedDistortion = val; }

private:
    double fCellWidth;
    double fAllowedDistortion;
};

} // namespace MACE::Core::Geometry::Description
