#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.h++"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.h++"
#include "MACE/DataModel/TransientData.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorAssign.h++"
#include "MACE/Utility/VectorCast.h++"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::inline Track {

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
    void VertexPosition(auto&& x) { fVertexPosition <<= std::forward<decltype(x)>(x); }
    void VertexMomentum(const stdx::array3d& p) { fVertexMomentum = p; }
    void VertexMomentum(auto&& p) { fVertexMomentum <<= std::forward<decltype(p)>(p); }
    void DecayTime(double val) { fDecayTime = val; }
    void DecayPosition(const stdx::array3d& x) { fDecayPosition = x; }
    void DecayPosition(auto&& x) { fDecayPosition <<= std::forward<decltype(x)>(x); }
    void DecayMomentum(const stdx::array3d& p) { fDecayMomentum = p; }
    void DecayMomentum(auto&& p) { fDecayMomentum <<= std::forward<decltype(p)>(p); }

    void FillAllBranchSocket() const& noexcept;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MTrk"sv; }

private:
    double fVertexTime;
    stdx::array3d fVertexPosition;
    stdx::array3d fVertexMomentum;
    double fDecayTime;
    stdx::array3d fDecayPosition;
    stdx::array3d fDecayMomentum;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static Vector3FBranchSocket fgVertexMomentum;
    static DoubleBranchSocket fgDecayTime;
    static Vector3FBranchSocket fgDecayPosition;
    static Vector3FBranchSocket fgDecayMomentum;
};
static_assert(TransientData<MuoniumTrack>);

} // namespace MACE::DataModel::inline Track
