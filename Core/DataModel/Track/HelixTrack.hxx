#pragma once

#include "DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector2BranchSocket.hxx"
#include "DataModel/DataHub.hxx"
#include "DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::Vector2FBranchSocket;

class HelixTrack : public ITransientData {
    friend DataHub;

public:
    HelixTrack() noexcept;
    HelixTrack(const HelixTrack&) noexcept = default;
    HelixTrack(HelixTrack&&) noexcept = default;
    virtual ~HelixTrack() noexcept = default;
    HelixTrack& operator=(const HelixTrack&) noexcept = default;
    HelixTrack& operator=(HelixTrack&&) noexcept = default;

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

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

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

inline void HelixTrack::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgCenter.SetValue(fCenter);
    fgRadius.SetValue(fRadius);
    fgZ0.SetValue(fZ0);
    fgAlpha.SetValue(fAlpha);
    fgNumberOfFittedPoints.SetValue(fNumberOfFittedPoints);
    fgChi2.SetValue(fChi2);
}

} // namespace MACE::Core::DataModel::Track
