#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hh"
#include "Reconstruction/Recognizer/HoughBase.hh"

template<class SpectrometerHitType>
class MACE::Reconstruction::Recognizer::HoughCartesian final :
    public MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType> {
    HoughCartesian(const HoughCartesian&) = delete;
    HoughCartesian& operator=(const HoughCartesian&) = delete;
private:
    using Base = MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>;
    using Hit = typename Base::Hit;
    using HitList = typename Base::HitList;
    using HitMap = typename Base::HitMap;
    template<typename T>
    using HoughSpace = typename Base::HoughSpace<T>;
    using HoughCoordinate = typename Base::HoughCoordinate;
    using RealCoordinate = typename Base::RealCoordinate;

public:
    HoughCartesian(Double_t houghSpaceExtent, Eigen::Index size, Double_t protectedRadius);
    ~HoughCartesian();

    void EnableHoughSpaceVisualization(bool val) { fEnableHoughSpaceVis = val; }
    void SaveLastRecognition(const char* fileName) override;

private:
    void HoughTransform() override;

    Double_t ToRealX(Eigen::Index i) const { return -fExtent + (i + 0.5) * fResolution; }
    Double_t ToRealY(Eigen::Index j) const { return -fExtent + (j + 0.5) * fResolution; }
    Eigen::Index ToHoughX(Double_t x) const { return (x + fExtent) / fResolution; }
    Eigen::Index ToHoughY(Double_t y) const { return (y + fExtent) / fResolution; }
    RealCoordinate ToRealCartesian(const HoughCoordinate& center) const override { return std::make_pair(ToRealX(center.first), ToRealY(center.second)); }

private:
    const Double_t fExtent;
    const Double_t fResolution;
    const Double_t fProtectedRadius;

    bool fEnableHoughSpaceVis = false;
    HoughSpace<size_t> fHoughSpaceVis;

    TFile* fFile = nullptr;
};

#include "Reconstruction/Recognizer/HoughCartesian.icc"