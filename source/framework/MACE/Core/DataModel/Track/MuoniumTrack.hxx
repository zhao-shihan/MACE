#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/stdx/array_alias.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Track {

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
    const auto& VertexMomentum() const { return fVertexMomentum; }
    const auto& GetDecayTime() const { return fDecayTime; }
    const auto& GetDecayPosition() const { return fDecayPosition; }
    const auto& GetDecayMomentum() const { return fDecayMomentum; }

    void VertexTime(double val) { fVertexTime = val; }
    void VertexPosition(auto&&... x)
        requires(sizeof...(x) >= 1)
    { Utility::AssignVector3D(fVertexPosition, std::forward<decltype(x)>(x)...); }
    void VertexMomentum(auto&&... p)
        requires(sizeof...(p) >= 1)
    { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void DecayTime(double val) { fDecayTime = val; }
    void DecayPosition(auto&&... x)
        requires(sizeof...(x) >= 1)
    { Utility::AssignVector3D(fDecayPosition, std::forward<decltype(x)>(x)...); }
    void DecayMomentum(auto&&... p)
        requires(sizeof...(p) >= 1)
    { Utility::AssignVector3D(fDecayMomentum, std::forward<decltype(p)>(p)...); }

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

} // namespace MACE::Core::DataModel::Track
