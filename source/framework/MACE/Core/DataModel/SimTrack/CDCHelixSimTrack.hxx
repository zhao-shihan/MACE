#pragma once

#include "MACE/Core/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <utility>
#include <string_view>

namespace MACE::Core::DataModel::Track {

using namespace std::string_view_literals;

class CDCPhysicsSimTrack;

class CDCHelixSimTrack : public CDCHelixTrack,
                         public CDCSimTrackBase {
public:
    CDCHelixSimTrack() noexcept;
    virtual ~CDCHelixSimTrack()  = default;

    CDCHelixSimTrack(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack(CDCHelixSimTrack&&) noexcept = default;
    CDCHelixSimTrack& operator=(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack& operator=(CDCHelixSimTrack&&) noexcept = default;

    explicit CDCHelixSimTrack(const CDCPhysicsSimTrack& physTrack, double B = 0.1_T);

    const auto& GetTrueCenter() const { return fTrueCenter; }
    const auto& GetTrueRadius() const { return fTrueRadius; }
    const auto& GetTrueZ0() const { return fTrueZ0; }
    const auto& GetTrueAlpha() const { return fTrueAlpha; }

    void SetTrueCenter(auto&&... c) requires(sizeof...(c) > 0) { Utility::AssignVector2D(fTrueCenter, std::forward<decltype(c)>(c)...); }
    void SetTrueRadius(double val) { fTrueRadius = val; }
    void SetTrueZ0(double val) { fTrueZ0 = val; }
    void SetTrueAlpha(double val) { fTrueAlpha = val; }

    auto CalcTruePhi0() const { return CDCTrackOperation::CalcHelixPhi0(fTrueCenter); }
    auto CalcTruePhi(const Eigen::Vector2d& point) const { return CDCTrackOperation::CalcHelixPhi(fTrueCenter, point); }
    auto CalcTruePhi(double x, double y) const { return CDCTrackOperation::CalcHelixPhi(fTrueCenter, x, y); }
    auto CalcTruePoint(double phi) { return CDCTrackOperation::CalcHelixPoint(std::tie(fTrueCenter, fTrueRadius, fTrueZ0, fTrueAlpha), phi); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "HlxSimTrk"sv; }

private:
    Eigen::Vector2d fTrueCenter;
    double fTrueRadius;
    double fTrueZ0;
    double fTrueAlpha;

    static BranchSocket::Vector2FBranchSocket fgTrueCenter;
    static BranchSocket::FloatBranchSocket fgTrueRadius;
    static BranchSocket::FloatBranchSocket fgTrueZ0;
    static BranchSocket::FloatBranchSocket fgTrueAlpha;
};
static_assert(TransientData<CDCHelixSimTrack>);

} // namespace MACE::Core::DataModel::Track
