#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/CDCHit.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::SimHit {

using namespace std::string_view_literals;

class CDCSimHit : public Hit::CDCHit {
public:
    CDCSimHit() noexcept;
    virtual ~CDCSimHit() = default;

    CDCSimHit(const CDCSimHit& hit) noexcept = default;
    CDCSimHit(CDCSimHit&& hit) noexcept = default;
    CDCSimHit& operator=(const CDCSimHit& hit) noexcept = default;
    CDCSimHit& operator=(CDCSimHit&& hit) noexcept = default;

    const auto& GetEnergy() const { return fEnergy; }
    const auto& GetMomentum() const { return fMomentum; }
    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetVertexEnergy() const { return fVertexEnergy; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetEnergy(double E) { fEnergy = E; }
    void SetMomentum(auto&&... p) requires(sizeof...(p) > 0) { Utility::AssignVector3D(fMomentum, std::forward<decltype(p)>(p)...); }
    void SetVertexTime(double val) { fVertexTime = val; }
    void SetVertexPosition(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector3D(fVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetVertexEnergy(double E) { fVertexEnergy = E; }
    void SetVertexMomentum(auto&&... p) requires(sizeof...(p) > 0) { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetParticle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }
    void SetG4EventID(int val) { fG4EventID = val; }
    void SetG4TrackID(int val) { fG4TrackID = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "CDCSimHit"sv; }

private:
    double fEnergy;
    Eigen::Vector3d fMomentum;
    double fVertexTime;
    Eigen::Vector3d fVertexPosition;
    double fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
    Utility::ShortString fParticle;
    int fG4EventID;
    int fG4TrackID;

    static BranchSocket::FloatBranchSocket fgEnergy;
    static BranchSocket::Vector3FBranchSocket fgMomentum;
    static BranchSocket::DoubleBranchSocket fgVertexTime;
    static BranchSocket::Vector3FBranchSocket fgVertexPosition;
    static BranchSocket::FloatBranchSocket fgVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgParticle;
    static BranchSocket::IntBranchSocket fgG4EventID;
    static BranchSocket::IntBranchSocket fgG4TrackID;
};
static_assert(TransientData<CDCSimHit>);

} // namespace MACE::Core::DataModel::SimHit
