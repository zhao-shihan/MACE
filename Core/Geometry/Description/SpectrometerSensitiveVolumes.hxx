#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4TwoVector.hh"

#include <tuple>
#include <vector>

namespace MACE::Core::Geometry::Description {

class SpectrometerSensitiveVolumes final : public IDescription {
public:
    static SpectrometerSensitiveVolumes& Instance() noexcept;

private:
    SpectrometerSensitiveVolumes() = default;
    ~SpectrometerSensitiveVolumes() noexcept = default;
    SpectrometerSensitiveVolumes(const SpectrometerSensitiveVolumes&) = delete;
    SpectrometerSensitiveVolumes& operator=(const SpectrometerSensitiveVolumes&) = delete;

public:
    std::string GetName() const override { return "SpectrometerSensitiveVolume"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetSensitiveWidth() const { return fSensitiveWidth; }
    /// @return Spectrometer sensitive volume info list. Subscript with layerID and get [ centerRadius, thick, half length, centerPhi, dPhi ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    std::vector<std::tuple<double, double, double, double, double>> GetInformationList() const;

    void SetSensitiveWidth(double val) { fSensitiveWidth = val; }

private:
    double fSensitiveWidth = 0.9;
};

} // namespace MACE::Core::Geometry::Description
