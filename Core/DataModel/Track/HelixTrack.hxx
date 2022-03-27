#pragma once

#include "DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector2BranchSocket.hxx"
#include "DataModel/DataHub.hxx"
#include "DataModel/ITransientData.hxx"
#include "LiteralUnit.hxx"
#include "PhysicalConstant.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::Vector2FBranchSocket;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class PhysicsTrack;

class HelixTrack : public ITransientData {
    friend DataHub;

public:
    HelixTrack() noexcept;
    HelixTrack(const HelixTrack&) noexcept = default;
    HelixTrack(HelixTrack&&) noexcept = default;
    virtual ~HelixTrack() noexcept = default;
    HelixTrack& operator=(const HelixTrack&) noexcept = default;
    HelixTrack& operator=(HelixTrack&&) noexcept = default;

    explicit HelixTrack(const PhysicsTrack& physTrack, Double_t B = 0.1_T);

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetCenter() const { return fCenter; }
    [[nodiscard]] const auto& GetRadius() const { return fRadius; }
    [[nodiscard]] const auto& GetZ0() const { return fZ0; }
    [[nodiscard]] const auto& GetAlpha() const { return fAlpha; }
    [[nodiscard]] const auto& GetNumberOfFittedPoints() const { return fNumberOfFittedPoints; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector2_t>
    void SetCenter(Vector2_t&& val) { fCenter = std::forward<Vector2_t>(val); }
    void SetCenter(Double_t x, Double_t y) { fCenter.Set(x, y); }
    void SetRadius(Double_t val) { fRadius = val; }
    void SetZ0(Double_t val) { fZ0 = val; }
    void SetAlpha(Double_t val) { fAlpha = val; }
    void SetNumberOfFittedPoints(Int_t n) { fNumberOfFittedPoints = n; }
    void SetChi2(Double_t val) { fChi2 = val; }

    [[nodiscard]] Double_t CalcPhi0() const noexcept { return std::atan2(-fCenter.fY, -fCenter.fX); }
    [[nodiscard]] TEveVectorD CalcPoint(Double_t phi, Double_t phi0) const noexcept;
    [[nodiscard]] TEveVectorD CalcPoint(Double_t phi) const noexcept { return CalcPoint(phi, CalcPhi0()); }
    [[nodiscard]] Double_t CalcPhi(Double_t x, Double_t y) const noexcept;
    template<typename Vector2_t>
    [[nodiscard]] Double_t CalcPhi(const Vector2_t& pos) const noexcept { return CalcPhi(pos[0], pos[1]); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "HlxTrk"; }

private:
    Double_t fVertexTime;
    TEveVector2D fCenter;
    Double_t fRadius;
    Double_t fZ0;
    Double_t fAlpha;
    Int_t fNumberOfFittedPoints;
    Double_t fChi2;

    static DoubleBranchSocket fgVertexTime;
    static Vector2FBranchSocket fgCenter;
    static FloatBranchSocket fgRadius;
    static FloatBranchSocket fgZ0;
    static FloatBranchSocket fgAlpha;
    static IntBranchSocket fgNumberOfFittedPoints;
    static FloatBranchSocket fgChi2;
};

} // namespace MACE::Core::DataModel::Track
