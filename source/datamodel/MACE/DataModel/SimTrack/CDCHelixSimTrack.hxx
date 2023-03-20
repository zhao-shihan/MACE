#pragma once

#include "MACE/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorArithmetic.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::inline Track {

using namespace std::string_view_literals;

class CDCPhysicsSimTrack;

class CDCHelixSimTrack : public CDCHelixTrack,
                         public CDCSimTrackBase {
public:
    CDCHelixSimTrack() noexcept;
    virtual ~CDCHelixSimTrack() = default;

    CDCHelixSimTrack(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack(CDCHelixSimTrack&&) noexcept = default;
    CDCHelixSimTrack& operator=(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack& operator=(CDCHelixSimTrack&&) noexcept = default;

    explicit CDCHelixSimTrack(const CDCPhysicsSimTrack& physTrack, double B = 0.1_T);

    const auto& GetTrueCenter() const { return fTrueCenter; }
    template<Concept::NumericVector3D T>
    auto GetTrueCenter() const { return VectorCast<T>(fTrueCenter); }
    const auto& GetTrueRadius() const { return fTrueRadius; }
    const auto& GetTrueZ0() const { return fTrueZ0; }
    const auto& GetTrueAlpha() const { return fTrueAlpha; }

    void SetTrueCenter(const stdx::array2d& c) { fTrueCenter = c; }
    void SetTrueCenter(auto&& c) { VectorAssign(fTrueCenter, std::forward<decltype(c)>(c)); }
    void SetTrueRadius(double val) { fTrueRadius = val; }
    void SetTrueZ0(double val) { fTrueZ0 = val; }
    void SetTrueAlpha(double val) { fTrueAlpha = val; }

    auto CalcTruePhi0() const { return CDCTrackOperation::CalcHelixPhi0(VectorCast<Eigen::Vector2d>(fTrueCenter)); }
    auto CalcTruePhi(const Eigen::Vector2d& point) const { return CDCTrackOperation::CalcHelixPhi(VectorCast<Eigen::Vector2d>(fTrueCenter), point); }
    auto CalcTruePhi(double x, double y) const { return CDCTrackOperation::CalcHelixPhi(VectorCast<Eigen::Vector2d>(fTrueCenter), x, y); }
    auto CalcTruePoint(double phi) { return CDCTrackOperation::CalcHelixPoint(std::tuple{VectorCast<Eigen::Vector2d>(fTrueCenter), fTrueRadius, fTrueZ0, fTrueAlpha}, phi); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "HlxSimTrk"sv; }

private:
    stdx::array2d fTrueCenter;
    double fTrueRadius;
    double fTrueZ0;
    double fTrueAlpha;

    static Vector2FBranchSocket fgTrueCenter;
    static FloatBranchSocket fgTrueRadius;
    static FloatBranchSocket fgTrueZ0;
    static FloatBranchSocket fgTrueAlpha;
};
static_assert(TransientData<CDCHelixSimTrack>);

} // namespace MACE::DataModel::inline Track
