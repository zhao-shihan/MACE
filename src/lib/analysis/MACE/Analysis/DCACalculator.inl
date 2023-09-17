namespace MACE::Analysis {

template<std::floating_point AFloat>
AFloat DCACalculator<AFloat>::Compute(const DataModel::CDCPhysicsTrack& cdcTrack, const DataModel::MCPHit& mcpHit) const{

    /* const auto charge = (particleName.back() == '+') ? 1 : (-1);
    const auto pXY = (charge > 0) ? (-std::sqrt(p.x() * p.x() + p.y() * p.y())) : std::sqrt(p.x() * p.x() + p.y() * p.y());

    const auto radius = -pXY / (charge * B * c_light);
    const auto center = Eigen::Vector2d(xV.x() - radius * (p.y() / pXY),
                                        xV.y() - radius * (-p.x() / pXY));
    const auto alpha = std::atan2(pXY, p.z()); */
}

template<std::floating_point AFloat>
AFloat DCACalculator<AFloat>::Compute(const DataModel::CDCHelixTrack& cdcTrack, const DataModel::MCPHit& mcpHit) const {
    return ComputePointCircleDCA(cdcTrack.Radius().Value(), cdcTrack.Center().Value(), mcpHit.Position().Value());
}

template<std::floating_point AFloat>
AFloat DCACalculator<AFloat>::ComputePointCircleDCA(const AFloat r, const stdx::array2<AFloat> center, const stdx::array2<AFloat> point) const{
    return std2b::abs(r - Math::Norm(point - center));
}

} // namespace MACE::Analysis
