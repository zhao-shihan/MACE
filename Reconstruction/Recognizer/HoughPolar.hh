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

    void SaveLastRecognition(const char* fileName) override;

    void SetHoughClusterScannerHoughPhiSize(Eigen::Index val) { fScannerDI = (val + 1) / 2; }
    void SetHoughClusterScannerHoughRhoSize(Eigen::Index val) { fScannerDJ = (val + 1) / 2; }

private:
    void HoughTransform() override;
    void VoteForCenter() override;
    void CenterClusterizaion() override;
    void GenerateResult() override;

    void ClusterizationImpl(std::list<CoordinateSet>::const_iterator candidate, std::vector<HoughCoordinate>& cluster);

    Double_t ToRealPhi(Eigen::Index i) const { return -M_PI + (i + 0.5) * fPhiResolution; }
    Double_t ToRealRho(Eigen::Index j) const { return fRhoLow + (j + 0.5) * fRhoResolution; }
    Eigen::Index ToHoughPhi(Double_t phi) const { return (phi + M_PI) / fPhiResolution; }
    Eigen::Index ToHoughRho(Double_t rho) const { return (rho - fRhoLow) / fRhoResolution; }

private:
    const Double_t fRhoLow;
    const Double_t fRhoUp;
    const Double_t fPhiResolution;
    const Double_t fRhoResolution;
    Eigen::Index fScannerDI = 3;
    Eigen::Index fScannerDJ = 4;

    TFile* fFile = nullptr;
};