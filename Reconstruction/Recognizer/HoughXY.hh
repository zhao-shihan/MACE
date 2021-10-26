#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hh"
#include "Reconstruction/Recognizer/HoughBase.hh"

class MACE::Reconstruction::Recognizer::HoughXY final :
    public MACE::Reconstruction::Recognizer::HoughBase {
    HoughXY(const HoughXY&) = delete;
    HoughXY& operator=(const HoughXY&) = delete;
public:
    HoughXY(Double_t houghSpaceExtent, Double_t proposingHoughSpaceResolution);
    ~HoughXY();

    void SaveLastRecognition(const char* fileName) override;

    void SetHoughClusterScannerRadialExtent(Double_t val) { fScannerDR = std::fabs(0.5 * val); }
    void SetHoughClusterScannerAngularExtent(Double_t val) { fScannerDPhi = std::fabs(0.5 * val); }

private:
    void HoughTransform() override;
    void VoteForCenter() override;
    void CenterClusterizaion() override;
    void GenerateResult() override;

    void ClusterizationImpl(std::list<CoordinateSet>::const_iterator candidate, std::vector<HoughCoordinate>& cluster);

    Double_t ToRealX(Eigen::Index i) const { return -fExtent + (i + 0.5) * fResolution; }
    Double_t ToRealY(Eigen::Index j) const { return -fExtent + (j + 0.5) * fResolution; }
    Eigen::Index ToHoughX(Double_t x) const { return (x + fExtent) / fResolution; }
    Eigen::Index ToHoughY(Double_t y) const { return (y + fExtent) / fResolution; }

private:
    const Double_t fExtent;
    const Double_t fResolution;
    Double_t fScannerDR = 100;
    Double_t fScannerDPhi = M_PI / 180;

    TFile* fFile = nullptr;
};