#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/ITransientData.hxx"

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
    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetDecayTime(Double_t val) { fDecayTime = val; }
    template<typename Vector3_t>
    void SetDecayPosition(Vector3_t&& pos) { fDecayPosition = std::forward<Vector3_t>(pos); }
    void SetDecayPosition(Double_t x, Double_t y, Double_t z) { fDecayPosition = {x, y, z}; }

    static consteval const char* BasicTreeName() noexcept { return "MTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fVertexTime;
    Eigen::Vector3d fVertexPosition;
    Double_t fDecayTime;
    Eigen::Vector3d fDecayPosition;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static DoubleBranchSocket fgDecayTime;
    static Vector3FBranchSocket fgDecayPosition;
};

} // namespace MACE::Simulation::SimTarget
