#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4RotationMatrix.hh"

#include <tuple>
#include <vector>

namespace MACE::Geometry::Description {

class SpectrometerCells final : public IDescription {
public:
    static SpectrometerCells& Instance() noexcept;

private:
    SpectrometerCells() = default;
    ~SpectrometerCells() noexcept = default;
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

public:
    std::string GetName() const override { return "SpectrometerCell"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    /// @return Cell info list. Subscript with layerID and get the list of [ angular width, half length, (sub-list)[ rotation ] ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> GetInformationList() const;
};

} // namespace MACE::Geometry::Description
