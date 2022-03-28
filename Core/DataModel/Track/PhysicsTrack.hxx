#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/Vector3BranchSocket.hxx"
#include "Core/DataModel/DataHub.hxx"
#include "Core/DataModel/ITransientData.hxx"
#include "Utility/LiteralUnit.hxx"
#include "Utility/PhysicalConstant.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;
using Utility::PhysicalConstant::electron_mass_c2;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class HelixTrack;

class PhysicsTrack : public ITransientData {
    friend DataHub;

public:
    PhysicsTrack() noexcept;
    PhysicsTrack(const PhysicsTrack&) noexcept = default;
    PhysicsTrack(PhysicsTrack&&) noexcept = default;
    virtual ~PhysicsTrack() noexcept = default;
    PhysicsTrack& operator=(const PhysicsTrack&) noexcept = default;
    PhysicsTrack& operator=(PhysicsTrack&&) noexcept = default;

    PhysicsTrack(const HelixTrack& helix, Double_t phiVertex = 0, Double_t B = 0.1_T, Double_t mass = electron_mass_c2);

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetVertexEnergy() const { return fVertexEnergy; }
    [[nodiscard]] const auto& GetVertexMomentum() const { return fVertexMomentum; }
    [[nodiscard]] const auto& GetParticle() const { return fParticle; }
    [[nodiscard]] const auto& GetNumberOfFittedPoints() const { return fNumberOfFittedPoints; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3_t>
    void SetVertexMomentum(Vector3_t&& mom) { fVertexMomentum = std::forward<Vector3_t>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum.Set(pX, pY, pZ); }
    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }
    void SetNumberOfFittedPoints(Int_t n) { fNumberOfFittedPoints = n; }
    void SetChi2(Double_t val) { fChi2 = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "PhyTrk"; }

private:
    Double_t fVertexTime;
    TEveVectorD fVertexPosition;
    Double_t fVertexEnergy;
    TEveVectorD fVertexMomentum;
    ShortString fParticle;
    Int_t fNumberOfFittedPoints;
    Double_t fChi2;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static FloatBranchSocket fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgNumberOfFittedPoints;
    static FloatBranchSocket fgChi2;
};

} // namespace MACE::Core::DataModel::Track
