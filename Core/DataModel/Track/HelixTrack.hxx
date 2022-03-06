#pragma once

#include "TEveVector.h"

#include "DataModel/Interface/Data.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::HelixTrack :
    public MACE::DataModel::Interface::Data {
    using Base = MACE::DataModel::Interface::Data;
    friend MACE::DataModel::DataHub;

public:
    HelixTrack() noexcept;
    HelixTrack(const HelixTrack& hit) noexcept = default;
    HelixTrack(HelixTrack&& hit) noexcept = default;
    virtual ~HelixTrack() noexcept = default;
    HelixTrack& operator=(const HelixTrack& hit) noexcept = default;
    HelixTrack& operator=(HelixTrack&& hit) noexcept = default;

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetCenter() const { return fCenter; }
    [[nodiscard]] const auto& GetRadius() const { return fRadius; }
    [[nodiscard]] const auto& GetZ0() const { return fZ0; }
    [[nodiscard]] const auto& GetAlpha() const { return fAlpha; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetCenter(const TEveVector2D& val) { fCenter = val; }
    void SetCenter(TEveVector2D&& val) { fCenter = std::move(val); }
    void SetCenter(Double_t x, Double_t y) { fCenter.Set(x, y); }
    void SetRadius(Double_t val) { fRadius = val; }
    void SetZ0(Double_t val) { fZ0 = val; }
    void SetAlpha(Double_t val) { fAlpha = val; }
    void SetChi2(Double_t val) { fChi2 = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "HlxTrk"; }

private:
    Double_t     fVertexTime;
    TEveVector2D fCenter;
    Double_t     fRadius;
    Double_t     fZ0;
    Double_t     fAlpha;
    Double_t     fChi2;

    static FloatBranchSocket    fgVertexTime;
    static Vector2FBranchSocket fgCenter;
    static FloatBranchSocket    fgRadius;
    static FloatBranchSocket    fgZ0;
    static FloatBranchSocket    fgAlpha;
    static FloatBranchSocket    fgChi2;
};

inline void MACE::DataModel::HelixTrack::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgVertexTime.Value() = fVertexTime;
    fgCenter.Value() = fCenter;
    fgRadius.Value() = fRadius;
    fgZ0.Value() = fZ0;
    fgAlpha.Value() = fAlpha;
    fgChi2.Value() = fChi2;
}
