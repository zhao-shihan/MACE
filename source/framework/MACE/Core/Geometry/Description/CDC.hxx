#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "G4RotationMatrix.hh"
#include "G4TwoVector.hh"

#include "Eigen/Core"

namespace MACE::Core::Geometry::Description {

class CDC final : public ISingletonDescription<CDC> {
    friend Environment::Memory::SingletonFactory;

private:
    CDC();
    ~CDC() noexcept = default;
    CDC(const CDC&) = delete;
    CDC& operator=(const CDC&) = delete;

public:
    const auto& GetGasInnerRadius() const { return fGasInnerRadius; }
    const auto& GetGasOuterRadius() const { return fGasOuterRadius; }
    const auto& GetGasInnerLength() const { return fGasInnerLength; }
    const auto& GetGasOuterLength() const { return fGasOuterLength; }
    const auto& GetCellWidth() const { return fCellWidth; }
    const auto& GetCellWidthDistortionAllowed() const { return fCellWidthDistortionAllowed; }
    const auto& GetFieldWireDiameter() const { return fFieldWireDiameter; }
    const auto& GetSenseWireDiameter() const { return fSenseWireDiameter; }
    const auto& GetSensitiveVolumeRelativeWidth() const { return fSensitiveVolumeRelativeWidth; }
    const auto& GetShellInnerThickness() const { return fShellInnerThickness; }
    const auto& GetShellSideThickness() const { return fShellSideThickness; }
    const auto& GetShellOuterThickness() const { return fShellOuterThickness; }

    void SetGasInnerRadius(double val) { fGasInnerRadius = val; }
    void SetGasOuterRadius(double val) { fGasOuterRadius = val; }
    void SetGasInnerLength(double val) { fGasInnerLength = val; }
    void SetGasOuterLength(double val) { fGasOuterLength = val; }
    void SetCellWidth(double val) { fCellWidth = val; }
    void SetCellWidthDistortionAllowed(double val) { fCellWidthDistortionAllowed = val; }
    void SetFieldWireDiameter(double val) { fFieldWireDiameter = val; }
    void SetSenseWireDiameter(double val) { fSenseWireDiameter = val; }
    void SetSensitiveVolumeRelativeWidth(double val) { fSensitiveVolumeRelativeWidth = val; }
    void SetShellInnerThickness(double val) { fShellInnerThickness = val; }
    void SetShellSideThickness(double val) { fShellSideThickness = val; }
    void SetShellOuterThickness(double val) { fShellOuterThickness = val; }

    /// @return CDC sense wire map. A list of [ wire position @ z=0, wire direction ].
    std::vector<std::pair<Eigen::Vector2d, Eigen::Vector3d>> SenseWireMap() const;

    // Next 5 methods should only use for geometry construction.
    // Try not to decode them unless really need.

    /// @return Layer's information list. Subscript with layerID and get [ layer center radius, thickness(=cellWidth), length/2, nCells ].
    /// @warning This method constructs a std::vector<std::tuple<...>> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<std::tuple<...>> like this for many times could lead to performance issue.
    std::vector<std::tuple<double, double, double, int>> LayerGeometryDetail() const;
    /// @return Cell info list. Subscript with layerID and get the list of [ angular width, half length, (sub-list)[ rotation ] ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance issue.
    std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> CellGeometryDetail() const;
    /// @return Field wire info list. Subscript with layerID and get [ half length, (sub-list)[ (local) position ] ].
    /// the sub-list contains 3 elements, represents the 3 field wire in a lattice.
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance issue.
    std::vector<std::pair<double, std::array<G4TwoVector, 3>>> FieldWireGeometryDetail() const;
    /// @return Sense wire's information map. Subscript with layerID and get [ position, half length ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance issue.
    std::vector<std::pair<G4TwoVector, double>> SenseWireGeometryDetail() const;
    /// @return Spectrometer sensitive volume info list. Subscript with layerID and get [ centerRadius, thick, half length, centerPhi, dPhi ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance issue.
    std::vector<std::tuple<double, double, double, double, double>> SensitiveVolumeGeometryDetail() const;

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fGasInnerRadius;
    double fGasOuterRadius;
    double fGasInnerLength;
    double fGasOuterLength;
    double fCellWidth;
    double fCellWidthDistortionAllowed;
    double fFieldWireDiameter;
    double fSenseWireDiameter;
    double fSensitiveVolumeRelativeWidth;
    double fShellInnerThickness;
    double fShellSideThickness;
    double fShellOuterThickness;
};

} // namespace MACE::Core::Geometry::Description
