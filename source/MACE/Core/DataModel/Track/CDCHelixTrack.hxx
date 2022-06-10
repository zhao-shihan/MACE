#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/Track/ICDCTrack.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::FloatBranchSocket;
using BranchSocket::Vector2FBranchSocket;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class CDCPhysicsTrack;

class CDCHelixTrack : public ICDCTrack {
public:
    CDCHelixTrack() noexcept;
    CDCHelixTrack(const CDCHelixTrack&) noexcept = default;
    CDCHelixTrack(CDCHelixTrack&&) noexcept = default;
    virtual ~CDCHelixTrack() noexcept = default;
    CDCHelixTrack& operator=(const CDCHelixTrack&) noexcept = default;
    CDCHelixTrack& operator=(CDCHelixTrack&&) noexcept = default;

    explicit CDCHelixTrack(const CDCPhysicsTrack& physTrack, Double_t B = 0.1_T);

    const auto& GetCenter() const { return fCenter; }
    const auto& GetRadius() const { return fRadius; }
    const auto& GetZ0() const { return fZ0; }
    const auto& GetAlpha() const { return fAlpha; }

    template<typename Vector2T>
    void SetCenter(Vector2T&& val) { fCenter = std::forward<Vector2T>(val); }
    void SetCenter(Double_t x, Double_t y) { fCenter = {x, y}; }
    void SetRadius(Double_t val) { fRadius = val; }
    void SetZ0(Double_t val) { fZ0 = val; }
    void SetAlpha(Double_t val) { fAlpha = val; }

    double CalcPhi0() const { return CDCTrackOperation::CalcHelixPhi0(fCenter); }
    double CalcPhi(const Eigen::Vector2d& point) const { return CDCTrackOperation::CalcHelixPhi(fCenter, point); }
    double CalcPhi(double x, double y) const { return CDCTrackOperation::CalcHelixPhi(fCenter, x, y); }
    Eigen::Vector3d CalcPoint(double phi) { return CDCTrackOperation::CalcHelixPoint(std::tie(fCenter, fRadius, fZ0, fAlpha), phi); }

    static consteval const char* BasicTreeName() noexcept { return "HlxTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Eigen::Vector2d fCenter;
    Double_t fRadius;
    Double_t fZ0;
    Double_t fAlpha;

    static Vector2FBranchSocket fgCenter;
    static FloatBranchSocket fgRadius;
    static FloatBranchSocket fgZ0;
    static FloatBranchSocket fgAlpha;
};

} // namespace MACE::Core::DataModel::Track
