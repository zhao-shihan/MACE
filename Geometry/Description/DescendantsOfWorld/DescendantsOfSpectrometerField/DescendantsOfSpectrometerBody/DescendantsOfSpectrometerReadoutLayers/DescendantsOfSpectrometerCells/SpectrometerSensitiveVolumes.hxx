#pragma once

#include <vector>

#include "G4TwoVector.hh"

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerSensitiveVolumes final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerSensitiveVolumes& Instance() noexcept;

private:
    SpectrometerSensitiveVolumes() noexcept = default;
    ~SpectrometerSensitiveVolumes() noexcept = default;
    SpectrometerSensitiveVolumes(const SpectrometerSensitiveVolumes&) = delete;
    SpectrometerSensitiveVolumes& operator=(const SpectrometerSensitiveVolumes&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerSensitiveVolume"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    /// @return Spectrometer sensitive volume info list. Subscript with cellID and get [ layerID, radius, (local) position ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    [[nodiscard]] std::vector<std::tuple<int, double, G4TwoVector>> GetInformationList() const;
};
