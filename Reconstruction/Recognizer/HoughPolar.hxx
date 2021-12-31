#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hxx"
#include "Reconstruction/Recognizer/HoughBase.hxx"

template<class SpectrometerHitType>
class MACE::Reconstruction::Recognizer::HoughPolar final :
    public MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType> {
    HoughPolar(const HoughPolar&) = delete;
    HoughPolar& operator=(const HoughPolar&) = delete;
private:
    using Base = MACE::Reconstruction::Recognizer::HoughBase<SpectrometerHitType>;
    using Hit = typename Base::Hit;
    using HitList = typename Base::HitList;
    using HoughSpace = typename Base::HoughSpace;
    using HoughCoordinate = typename Base::HoughCoordinate;
    using RealCoordinate = typename Base::RealCoordinate;

public:
    HoughPolar(Double_t innerRadius, Double_t outerRadius, Eigen::Index nPhis, Eigen::Index nRhos);
    ~HoughPolar();

    void EnableHoughSpaceVisualization(bool val) { fEnableHoughSpaceVis = val; }
    void SaveLastRecognition(const char* fileName) override;

private:
    void HoughTransform() override;

    Double_t ToRealPhi(Eigen::Index i) const { return -M_PI + (i + 0.5) * fPhiResolution; }
    Double_t ToRealRho(Eigen::Index j) const { return fRhoLow + (j + 0.5) * fRhoResolution; }
    Eigen::Index ToHoughPhi(Double_t phi) const { return (phi + M_PI) / fPhiResolution; }
    Eigen::Index ToHoughRho(Double_t rho) const { return (rho - fRhoLow) / fRhoResolution; }
    RealCoordinate ToRealCartesian(const HoughCoordinate& center) const override {
        auto centerPhi = ToRealPhi(center.first);
        auto centerRho = ToRealRho(center.second);
        return std::make_pair(cos(centerPhi) / centerRho, sin(centerPhi) / centerRho);
    }

private:
    const Double_t fRhoLow;
    const Double_t fRhoUp;
    const Double_t fPhiResolution;
    const Double_t fRhoResolution;

    bool fEnableHoughSpaceVis = false;
    Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic> fHoughSpaceVis;

    TFile* fFile = nullptr;
};

#include "Reconstruction/Recognizer/HoughPolar.txx"