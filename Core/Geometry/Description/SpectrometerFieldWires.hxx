#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4TwoVector.hh"

#include <array>
#include <vector>

namespace MACE::Geometry::Description {

class SpectrometerFieldWires final : public IDescription {
public:
    static SpectrometerFieldWires& Instance() noexcept;

private:
    SpectrometerFieldWires() = default;
    ~SpectrometerFieldWires() noexcept = default;
    SpectrometerFieldWires(const SpectrometerFieldWires&) = delete;
    SpectrometerFieldWires& operator=(const SpectrometerFieldWires&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "SpectrometerFieldWire"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetDiameter() const { return fDiameter; }
    /// @return Field wire info list. Subscript with layerID and get [ half length, (sub-list)[ (local) position ] ].
    /// the sub-list contains 3 elements, represents the 3 field wire in a lattice.
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    [[nodiscard]] std::vector<std::pair<double, std::array<G4TwoVector, 3>>> GetInformationList() const;

    void SetFieldWireDiameter(double val) { fDiameter = val; }

private:
    double fDiameter = 110_um;
};

} // namespace MACE::Geometry::Description
