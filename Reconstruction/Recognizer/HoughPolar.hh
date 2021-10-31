#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hh"
#include "Reconstruction/Recognizer/HoughBase.hh"

class MACE::Reconstruction::Recognizer::HoughPolar final :
    public MACE::Reconstruction::Recognizer::HoughBase {
    HoughPolar(const HoughPolar&) = delete;
    HoughPolar& operator=(const HoughPolar&) = delete;
public:
    HoughPolar(Double_t innerRadius, Double_t outerRadius, Eigen::Index nPhis, Eigen::Index nRhos);
    ~HoughPolar();

    void EnableHoughSpaceVisualization(bool val) { fEnableHoughSpaceVis = val; }
    void SaveLastRecognition(const char* fileName) override;

private:
    void HoughTransform() override;

    Double_t ToReal1(Eigen::Index i) const override { return -M_PI + (i + 0.5) * fPhiResolution; }
    Double_t ToReal2(Eigen::Index j) const override { return fRhoLow + (j + 0.5) * fRhoResolution; }
    Eigen::Index ToHough1(Double_t phi) const override { return (phi + M_PI) / fPhiResolution; }
    Eigen::Index ToHough2(Double_t rho) const override { return (rho - fRhoLow) / fRhoResolution; }
    Double_t Cross(const CLHEP::Hep3Vector& hitPos, const RealCoordinate& center) const override;

private:
    const Double_t fRhoLow;
    const Double_t fRhoUp;
    const Double_t fPhiResolution;
    const Double_t fRhoResolution;

    bool fEnableHoughSpaceVis = false;
    HoughSpace<size_t> fHoughSpaceVis;

    TFile* fFile = nullptr;
};