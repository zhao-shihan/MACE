#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/stdx/array_alias.hxx"
#include "MACE/Utility/AssignVector.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Track {

using namespace std::string_view_literals;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class CDCPhysicsTrack;

class CDCHelixTrack : public CDCTrackBase {
public:
    CDCHelixTrack() noexcept;
    virtual ~CDCHelixTrack() = default;

    CDCHelixTrack(const CDCHelixTrack&) noexcept = default;
    CDCHelixTrack(CDCHelixTrack&&) noexcept = default;
    CDCHelixTrack& operator=(const CDCHelixTrack&) noexcept = default;
    CDCHelixTrack& operator=(CDCHelixTrack&&) noexcept = default;

    explicit CDCHelixTrack(const CDCPhysicsTrack& physTrack, double B = 0.1_T);

    const auto& GetCenter() const { return fCenter; }
    const auto& Radius() const { return fRadius; }
    const auto& GetZ0() const { return fZ0; }
    const auto& GetAlpha() const { return fAlpha; }

    void SetCenter(auto&&... c)
        requires(sizeof...(c) > 0)
    { Utility::AssignVector2D(fCenter, std::forward<decltype(c)>(c)...); }
    void Radius(double val) { fRadius = val; }
    void SetZ0(double val) { fZ0 = val; }
    void SetAlpha(double val) { fAlpha = val; }

    auto CalcPhi0() const { return CDCTrackOperation::CalcHelixPhi0(Utility::Vector2Cast<Eigen::Vector2d>(fCenter)); }
    auto CalcPhi(const Eigen::Vector2d& point) const { return CDCTrackOperation::CalcHelixPhi(Utility::Vector2Cast<Eigen::Vector2d>(fCenter), point); }
    auto CalcPhi(double x, double y) const { return CDCTrackOperation::CalcHelixPhi(Utility::Vector2Cast<Eigen::Vector2d>(fCenter), x, y); }
    auto CalcPoint(double phi) { return CDCTrackOperation::CalcHelixPoint(std::tuple{Utility::Vector2Cast<Eigen::Vector2d>(fCenter), fRadius, fZ0, fAlpha}, phi); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "HlxTrk"sv; }

private:
    stdx::array2d fCenter;
    double fRadius;
    double fZ0;
    double fAlpha;

    static BranchSocket::Vector2FBranchSocket fgCenter;
    static BranchSocket::FloatBranchSocket fgRadius;
    static BranchSocket::FloatBranchSocket fgZ0;
    static BranchSocket::FloatBranchSocket fgAlpha;
};
static_assert(TransientData<CDCHelixTrack>);

} // namespace MACE::Core::DataModel::Track
