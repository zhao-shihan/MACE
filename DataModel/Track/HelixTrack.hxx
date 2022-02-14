#pragma once

#include "TEveVector.h"

#include "DataModel/Global.hxx"
#include "DataModel/Interface/Data.hxx"

class MACE::DataModel::HelixTrack :
    private MACE::DataModel::Interface::Data {
public:
    HelixTrack() noexcept;
    HelixTrack(const HelixTrack& hit) noexcept;
    HelixTrack(HelixTrack&& hit) noexcept;
    virtual ~HelixTrack() noexcept = default;
    HelixTrack& operator=(const HelixTrack& hit) noexcept;
    HelixTrack& operator=(HelixTrack&& hit) noexcept;

    static constexpr const char* Name() { return "HlxTrk"; }
    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetCenter() const { return fCenter; }
    const auto& GetRadius() const { return fRadius; }
    const auto& GetZ0() const { return fZ0; }
    const auto& GetAlpha() const { return fAlpha; }
    const auto& GetChi2() const { return fChi2; }

    void SetCenter(const TEveVector2D& val) { fCenter = val; }
    void SetCenter(TEveVector2D&& val) { fCenter = std::move(val); }
    void SetCenter(Double_t x, Double_t y) { fCenter.Set(x, y); }
    void SetRadius(Double_t val) { fRadius = val; }
    void SetZ0(Double_t val) { fZ0 = val; }
    void SetAlpha(Double_t val) { fAlpha = val; }
    void SetChi2(Double_t val) { fChi2 = val; }

private:
    TEveVector2D fCenter;
    Double_t fRadius;
    Double_t fZ0;
    Double_t fAlpha;
    Double_t fChi2;

    static Column<Float_t> fgCenterX;
    static Column<Float_t> fgCenterY;
    static Column<Float_t> fgRadius;
    static Column<Float_t> fgZ0;
    static Column<Float_t> fgAlpha;
    static Column<Float_t> fgChi2;
};

inline void MACE::DataModel::HelixTrack::FillBranches() noexcept {
    Interface::Data::FillBranches();
    fgCenterX.value = fCenter.fX;
    fgCenterY.value = fCenter.fY;
    fgRadius.value = fRadius;
    fgZ0.value = fZ0;
    fgAlpha.value = fAlpha;
    fgChi2.value = fChi2;
}
