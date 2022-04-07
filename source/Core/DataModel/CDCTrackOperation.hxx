#pragma once

#include "Utility/LiteralUnit.hxx"
#include "Utility/PhysicalConstant.hxx"
#include "Utility/ShortString.hxx"

#include "Eigen/Core"

#include <tuple>

namespace MACE::Core::DataModel::CDCTrackOperation {

using Utility::ShortString;
using Utility::PhysicalConstant::electron_mass_c2;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

using HelixTrackParameters = std::tuple<Eigen::Vector2d, double, double, double>;
using PhysicsTrackParameters = std::tuple<Eigen::Vector3d, double, Eigen::Vector3d, ShortString>;

/// @brief Calculate point on a helix track.
/// @param center The helix center.
/// @param phi The polar angle.
/// @return Space point respect to phi.
inline double CalcHelixPhi0(const Eigen::Vector2d& center) { return std::atan2(-center.y(), -center.x()); }

/// @brief Calculate point <-> helix track CPA's polar angle.
/// @param helix The helix center.
/// @param radius The helix radius.
/// @param x The x component of the point.
/// @param y The y component of the point.
double CalcHelixPhi(const Eigen::Vector2d& center, double x, double y);
inline double CalcHelixPhi(const Eigen::Vector2d& center, const Eigen::Vector2d& point) { return CalcHelixPhi(center, point.x(), point.y()); }

/// @brief Calculate point on a helix track.
/// @param helix The helix: [center, radius, z0, alpha].
/// @param phi The polar angle.
/// @return Space point respect to phi.
Eigen::Vector3d CalcHelixPoint(const HelixTrackParameters& helix, double phi);

/// @brief Convert physics track parameter to helix parameter.
/// @param physTrack Track physics parameters [vertex position, vertex energy, vertex momentum, particle name] to be converted.
/// @param B Magnetic flux density of spectrometer.
/// @return Helix parameter [center, radius, z0, alpha]
HelixTrackParameters ConvertToHelixParameters(const PhysicsTrackParameters& physTrack,
                                              double B = 0.1_T);

/// @brief Convert helix track parameter to physics parameter.
/// @param helix Track helix parameter [center, radius, z0, alpha] to be converted.
/// @param phiVertex Polar angle of vertex position. Relative to helix center, begin at z0.
/// @param B Magnetic flux density of spectrometer.
/// @param mass Particle mass.
/// @return Physics parameters [vertex position, vertex energy, vertex momentum, particle name]
PhysicsTrackParameters ConvertToPhysicsParameters(const HelixTrackParameters& helix,
                                                  double phiVertex = 0,
                                                  double B = 0.1_T,
                                                  double mass = electron_mass_c2);

} // namespace MACE::Core::DataModel::CDCTrackOperation
