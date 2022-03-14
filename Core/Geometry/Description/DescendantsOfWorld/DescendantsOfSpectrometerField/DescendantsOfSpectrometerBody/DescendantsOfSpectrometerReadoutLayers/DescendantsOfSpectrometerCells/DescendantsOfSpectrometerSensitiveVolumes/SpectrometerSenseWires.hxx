#pragma once

#include <vector>

#include "G4TwoVector.hh"

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerSenseWires final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerSenseWires& Instance() noexcept;

private:
    SpectrometerSenseWires() = default;
    ~SpectrometerSenseWires() noexcept = default;
    SpectrometerSenseWires(const SpectrometerSenseWires&) = delete;
    SpectrometerSenseWires& operator=(const SpectrometerSenseWires&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerSenseWire"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetDiameter() const { return fDiameter; }
    /// @return Sense wire's information map. Subscript with layerID and get [ position, half length ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    [[nodiscard]] std::vector<std::pair<G4TwoVector, double>> GetInformationList() const;

private:
    double fDiameter = 25_um;
};
