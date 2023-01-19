#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/Utility/AssignVector.hxx"

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

    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetDecayTime() const { return fDecayTime; }
    const auto& GetDecayPosition() const { return fDecayPosition; }
    const auto& GetDecayMomentum() const { return fDecayMomentum; }

    void SetVertexTime(double val) { fVertexTime = val; }
    void SetVertexPosition(auto&&... x)
        requires(sizeof...(x) > 0)
    { Utility::AssignVector3D(fVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetVertexMomentum(auto&&... p)
        requires(sizeof...(p) > 0)
    { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetDecayTime(double val) { fDecayTime = val; }
    void SetDecayPosition(auto&&... x)
        requires(sizeof...(x) > 0)
    { Utility::AssignVector3D(fDecayPosition, std::forward<decltype(x)>(x)...); }
    void SetDecayMomentum(auto&&... p)
        requires(sizeof...(p) > 0)
    { Utility::AssignVector3D(fDecayMomentum, std::forward<decltype(p)>(p)...); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MTrk"sv; }

private:
    double fVertexTime;
    Eigen::Vector3d fVertexPosition;
    Eigen::Vector3d fVertexMomentum;
    double fDecayTime;
    Eigen::Vector3d fDecayPosition;
    Eigen::Vector3d fDecayMomentum;

    static BranchSocket::DoubleBranchSocket fgVertexTime;
    static BranchSocket::Vector3FBranchSocket fgVertexPosition;
    static BranchSocket::Vector3FBranchSocket fgVertexMomentum;
    static BranchSocket::DoubleBranchSocket fgDecayTime;
    static BranchSocket::Vector3FBranchSocket fgDecayPosition;
    static BranchSocket::Vector3FBranchSocket fgDecayMomentum;
};
static_assert(TransientData<MuoniumTrack>);

} // namespace MACE::Core::DataModel::Track
