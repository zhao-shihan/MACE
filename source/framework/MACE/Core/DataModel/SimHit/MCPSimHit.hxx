#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/MCPHit.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::SimHit {

using namespace std::string_view_literals;

class MCPSimHit : public Hit::MCPHit {
public:
    MCPSimHit() noexcept;
    MCPSimHit(const MCPSimHit& hit) noexcept = default;
    MCPSimHit(MCPSimHit&& hit) noexcept = default;
    virtual ~MCPSimHit() noexcept = default;
    MCPSimHit& operator=(const MCPSimHit& hit) noexcept = default;
    MCPSimHit& operator=(MCPSimHit&& hit) noexcept = default;

    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetVertexTime(double val) { fVertexTime = val; }
    void SetVertexPosition(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector3D(fVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetParticle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }
    void SetG4EventID(int val) { fG4EventID = val; }
    void SetG4TrackID(int val) { fG4TrackID = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MCPSimHit"sv; }

private:
    double fVertexTime;
    Eigen::Vector3d fVertexPosition;
    Utility::ShortString fParticle;
    int fG4EventID;
    int fG4TrackID;

    static BranchSocket::DoubleBranchSocket fgVertexTime;
    static BranchSocket::Vector3FBranchSocket fgVertexPosition;
    static BranchSocket::ShortStringBranchSocket fgParticle;
    static BranchSocket::IntBranchSocket fgG4EventID;
    static BranchSocket::IntBranchSocket fgG4TrackID;
};
static_assert(TransientData<MCPSimHit>);

} // namespace MACE::Core::DataModel::SimHit
