#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::Core::DataModel::CDCTrackOperation {

double CalcHelixPhi(const Eigen::Vector2d& center, double x, double y) {
    const Eigen::Vector2d local(x - center.x(), y - center.y());
    const auto absPhi = std::acos(-center.dot(local)) / std::sqrt(center.squaredNorm() * local.squaredNorm());
    return (center.y() * local.x() - local.y() * center.x() > 0) ? absPhi : (-absPhi);
}

Eigen::Vector3d CalcHelixPoint(const HelixTrackParameters& helix, double phi) {
    const auto& [center, radius, z0, alpha] = helix;
    const auto phi0 = CalcHelixPhi0(center);
    return Eigen::Vector3d(center.x() + radius * std::cos(phi + phi0),
                           center.y() + radius * std::sin(phi + phi0),
                           z0 + radius * phi / std::tan(alpha));
}

HelixTrackParameters ConvertToHelixParameters(const PhysicsTrackParameters& physTrack,
                                              double B) {
    using Utility::PhysicalConstant::c_light;

    const auto& [xV, _, p, particleName] = physTrack;

    const auto charge = (particleName.back() == '+') ? 1 : (-1);
    const auto pPhi = (charge > 0) ? (-std::sqrt(p.x() * p.x() + p.y() * p.y())) : std::sqrt(p.x() * p.x() + p.y() * p.y());

    const auto radius = -pPhi / (charge * B * c_light);
    const auto center = Eigen::Vector2d(xV.x() - radius * (p.y() / pPhi),
                                        xV.y() - radius * (-p.x() / pPhi));
    const auto alpha = std::atan2(pPhi, p.z());

    return std::make_tuple(center,
                           radius,
                           xV.z() - radius * CalcHelixPhi(center, xV.x(), xV.y()) / std::tan(alpha),
                           alpha);
}

PhysicsTrackParameters ConvertToPhysicsParameters(const HelixTrackParameters& helix,
                                                  double phiVertex,
                                                  double B,
                                                  double mass) {
    using Utility::PhysicalConstant::c_light;

    const auto& [center, radius, z0, alpha] = helix;

    const auto charge = (alpha > 0) ? (-1) : 1;
    const auto pPhi = -charge * B * radius * c_light;
    const auto phi0 = CalcHelixPhi0(center);

    const auto vertexPosition = CalcHelixPoint(helix, phiVertex);
    const auto vertexMomentum = Eigen::Vector3d(-pPhi * std::sin(phiVertex + phi0),
                                                pPhi * std::cos(phiVertex + phi0),
                                                pPhi / std::tan(alpha));
    const auto vertexEnergy = std::sqrt(vertexMomentum.squaredNorm() + mass * mass);
    const auto particle = (charge > 0) ? "e+" : "e-";

    return std::make_tuple(vertexPosition, vertexEnergy, vertexMomentum, particle);
}

} // namespace MACE::Core::DataModel::CDCTrackOperation
