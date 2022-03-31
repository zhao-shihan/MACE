#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4TwoVector.hh"

#include <vector>

namespace MACE::Core::Geometry::Description {

class SpectrometerSenseWires final : public IDescription {
public:
    static SpectrometerSenseWires& Instance() noexcept;

private:
    SpectrometerSenseWires();
    ~SpectrometerSenseWires() noexcept = default;
    SpectrometerSenseWires(const SpectrometerSenseWires&) = delete;
    SpectrometerSenseWires& operator=(const SpectrometerSenseWires&) = delete;

public:
    const auto& GetDiameter() const { return fDiameter; }
    /// @return Sense wire's information map. Subscript with layerID and get [ position, half length ].
    /// @warning This method constructs a std::vector<...> according to current Description status,
    /// thus may become invalid after some Set..., invoke it after any Set method.
    /// @attention Keep the return value instead of invoke mutiple times if you need to check up the cell info.
    /// Otherwise constructs a std::vector<...> like this for many times could lead to performance problem.
    std::vector<std::pair<G4TwoVector, double>> GetInformationList() const;

private:
    double fDiameter;
};

} // namespace MACE::Core::Geometry::Description
