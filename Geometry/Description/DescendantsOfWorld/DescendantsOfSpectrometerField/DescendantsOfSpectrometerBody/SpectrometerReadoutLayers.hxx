#pragma once

#include <vector>

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerReadoutLayers final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerReadoutLayers& Instance() noexcept;

private:
    SpectrometerReadoutLayers() = default;
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerReadoutLayer"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "Readout layer of MWDC. Mother volume of cells and field wires."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Helium based gas."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "Tube."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerBody"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetThickness() const { return fLayerThickness; }
    /// @return Layer's information list. Subscript with layerID and get [ layer center's radius, length/2 ].
    /// @warning This method constructs a std::vector<std::tuple<...>> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<std::tuple<...>> like this for many times could lead to performance problem.
    [[nodiscard]] std::vector<std::pair<double, double>> GetInformationList() const;

    void SetLayerThickness(double val) { fLayerThickness = val; }

private:
    double fLayerThickness = 10_mm;
};
