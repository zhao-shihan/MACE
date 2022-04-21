#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"

#include "G4ThreeVector.hh"

namespace MACE::Simulation::SimTarget {

using Core::DataModel::BranchSocket::DoubleBranchSocket;
using Core::DataModel::BranchSocket::Vector3FBranchSocket;

class MuoniumTrack : public Core::DataModel::ITransientData {
public:
    MuoniumTrack() noexcept;
    MuoniumTrack(const MuoniumTrack& trk) noexcept = default;
    MuoniumTrack(MuoniumTrack&& trk) noexcept = default;
    virtual ~MuoniumTrack() noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack& trk) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&& trk) noexcept = default;

    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetDecayTime() const { return fDecayTime; }
    const auto& GetDecayPosition() const { return fDecayPosition; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetVertexPosition(const G4ThreeVector& pos) { SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(Double_t px, Double_t py, Double_t pz) { fVertexMomentum = {px, py, pz}; }
    void SetVertexMomentum(const G4ThreeVector& mom) { SetVertexMomentum(mom.x(), mom.y(), mom.z()); }
    void SetDecayTime(Double_t val) { fDecayTime = val; }
    void SetDecayPosition(Double_t x, Double_t y, Double_t z) { fDecayPosition = {x, y, z}; }
    void SetDecayPosition(const G4ThreeVector& pos) { SetDecayPosition(pos.x(), pos.y(), pos.z()); }
    void SetDecayMomentum(Double_t px, Double_t py, Double_t pz) { fDecayMomentum = {px, py, pz}; }
    void SetDecayMomentum(const G4ThreeVector& mom) { SetDecayMomentum(mom.x(), mom.y(), mom.z()); }

    static consteval const char* BasicTreeName() noexcept { return "MTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fVertexTime;
    Eigen::Vector3d fVertexPosition;
    Eigen::Vector3d fVertexMomentum;
    Double_t fDecayTime;
    Eigen::Vector3d fDecayPosition;
    Eigen::Vector3d fDecayMomentum;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static Vector3FBranchSocket fgVertexMomentum;
    static DoubleBranchSocket fgDecayTime;
    static Vector3FBranchSocket fgDecayPosition;
    static Vector3FBranchSocket fgDecayMomentum;
};

} // namespace MACE::Simulation::SimTarget
