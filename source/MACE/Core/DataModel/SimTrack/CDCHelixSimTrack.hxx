#pragma once

#include "MACE/Core/DataModel/SimTrack/ICDCSimTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"

namespace MACE::Core::DataModel::Track {

class CDCPhysicsSimTrack;

class CDCHelixSimTrack : public CDCHelixTrack,
                         public ICDCSimTrack {
public:
    CDCHelixSimTrack() noexcept;
    CDCHelixSimTrack(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack(CDCHelixSimTrack&&) noexcept = default;
    virtual ~CDCHelixSimTrack() noexcept = default;
    CDCHelixSimTrack& operator=(const CDCHelixSimTrack&) noexcept = default;
    CDCHelixSimTrack& operator=(CDCHelixSimTrack&&) noexcept = default;

    explicit CDCHelixSimTrack(const CDCPhysicsSimTrack& physTrack, Double_t B = 0.1_T);

    const auto& GetTrueCenter() const { return fTrueCenter; }
    const auto& GetTrueRadius() const { return fTrueRadius; }
    const auto& GetTrueZ0() const { return fTrueZ0; }
    const auto& GetTrueAlpha() const { return fTrueAlpha; }

    template<typename Vector2_t>
    void SetTrueCenter(Vector2_t&& val) { fTrueCenter = std::forward<Vector2_t>(val); }
    void SetTrueCenter(Double_t x, Double_t y) { fTrueCenter = {x, y}; }
    void SetTrueRadius(Double_t val) { fTrueRadius = val; }
    void SetTrueZ0(Double_t val) { fTrueZ0 = val; }
    void SetTrueAlpha(Double_t val) { fTrueAlpha = val; }

    double CalcTruePhi0() const { return CDCTrackOperation::CalcHelixPhi0(fTrueCenter); }
    double CalcTruePhi(const Eigen::Vector2d& point) const { return CDCTrackOperation::CalcHelixPhi(fTrueCenter, point); }
    double CalcTruePhi(double x, double y) const { return CDCTrackOperation::CalcHelixPhi(fTrueCenter, x, y); }
    Eigen::Vector3d CalcTruePoint(double phi) { return CDCTrackOperation::CalcHelixPoint(std::tie(fTrueCenter, fTrueRadius, fTrueZ0, fTrueAlpha), phi); }

    static consteval const char* BasicTreeName() noexcept { return "HlxSimTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Eigen::Vector2d fTrueCenter;
    Double_t fTrueRadius;
    Double_t fTrueZ0;
    Double_t fTrueAlpha;

    static Vector2FBranchSocket fgTrueCenter;
    static FloatBranchSocket fgTrueRadius;
    static FloatBranchSocket fgTrueZ0;
    static FloatBranchSocket fgTrueAlpha;
};

} // namespace MACE::Core::DataModel::Track
