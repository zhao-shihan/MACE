#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hh"
#include "Reconstruction/Recognizer/HoughBase.hh"

class MACE::Reconstruction::Recognizer::HoughPolar final :
    public MACE::Reconstruction::Recognizer::HoughBase {
    HoughPolar(const HoughPolar&) = delete;
    HoughPolar& operator=(const HoughPolar&) = delete;
public:
    HoughPolar(Double_t protectedRadius, Eigen::Index nRhos, Eigen::Index nPhis);
    ~HoughPolar();

    void SaveLastRecognition(const char* fileName) override;

    void SetHoughClusterScannerHoughRhoSize(Eigen::Index val) { fScannerDI = (val + 1) / 2; }
    void SetHoughClusterScannerHoughPhiSize(Eigen::Index val) { fScannerDJ = (val + 1) / 2; }
    void SetHoughClusterScannerRealRhoSize(Double_t val) { SetHoughClusterScannerHoughRhoSize(round(val / fRhoResolution)); }
    void SetHoughClusterScannerRealPhiSize(Double_t val) { SetHoughClusterScannerHoughPhiSize(round(val / fPhiResolution)); }

private:
    void HoughTransform() override;
    void VoteForCenter() override;
    void CenterClusterizaion() override;
    void GenerateResult() override;

    void ClusterizationImpl(std::list<CoordinateSet>::const_iterator candidate, std::vector<HoughCoordinate>& cluster);

    Double_t ToRealRho(Eigen::Index i) const { return (i + 0.5) * fRhoResolution; }
    Double_t ToRealPhi(Eigen::Index j) const { return -M_PI + (j + 0.5) * fPhiResolution; }
    Eigen::Index ToHoughRho(Double_t rho) const { return rho / fRhoResolution; }
    Eigen::Index ToHoughPhi(Double_t phi) const { return (phi + M_PI) / fPhiResolution; }

private:
    const Double_t fRhoResolution;
    const Double_t fPhiResolution;
    Eigen::Index fScannerDI = 2;
    Eigen::Index fScannerDJ = 2;

    TFile* fFile = nullptr;
};