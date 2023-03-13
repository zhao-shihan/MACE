#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::Track {

using namespace std::string_view_literals;

class MuoniumTrack {
public:
    MuoniumTrack() noexcept;
    virtual ~MuoniumTrack() = default;

    MuoniumTrack(const MuoniumTrack&) noexcept = default;
    MuoniumTrack(MuoniumTrack&&) noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack&) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&&) noexcept = default;

    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    template<Concept::NumericVector3D T>
    auto VertexPosition() const { return VectorCast<T>(fVertexPosition); }
    const auto& VertexMomentum() const { return fVertexMomentum; }
    template<Concept::NumericVector3D T>
    auto VertexMomentum() const { return VectorCast<T>(fVertexMomentum); }
    const auto& DecayTime() const { return fDecayTime; }
    const auto& DecayPosition() const { return fDecayPosition; }
    const auto& DecayMomentum() const { return fDecayMomentum; }

    void VertexTime(double val) { fVertexTime = val; }
    void VertexPosition(const stdx::array3d& x) { fVertexPosition = x; }
    void VertexPosition(auto&& x) { VectorAssign(fVertexPosition, std::forward<decltype(x)>(x)); }
    void VertexMomentum(const stdx::array3d& p) { fVertexMomentum = p; }
    void VertexMomentum(auto&& p) { VectorAssign(fVertexMomentum, std::forward<decltype(p)>(p)); }
    void DecayTime(double val) { fDecayTime = val; }
    void DecayPosition(const stdx::array3d& x) { fDecayPosition = x; }
    void DecayPosition(auto&& x) { VectorAssign(fDecayPosition, std::forward<decltype(x)>(x)); }
    void DecayMomentum(const stdx::array3d& p) { fDecayMomentum = p; }
    void DecayMomentum(auto&& p) { VectorAssign(fDecayMomentum, std::forward<decltype(p)>(p)); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MTrk"sv; }

private:
    double fVertexTime;
    stdx::array3d fVertexPosition;
    stdx::array3d fVertexMomentum;
    double fDecayTime;
    stdx::array3d fDecayPosition;
    stdx::array3d fDecayMomentum;

    static BranchSocket::DoubleBranchSocket fgVertexTime;
    static BranchSocket::Vector3FBranchSocket fgVertexPosition;
    static BranchSocket::Vector3FBranchSocket fgVertexMomentum;
    static BranchSocket::DoubleBranchSocket fgDecayTime;
    static BranchSocket::Vector3FBranchSocket fgDecayPosition;
    static BranchSocket::Vector3FBranchSocket fgDecayMomentum;
};
static_assert(TransientData<MuoniumTrack>);

} // namespace MACE::DataModel::Track
