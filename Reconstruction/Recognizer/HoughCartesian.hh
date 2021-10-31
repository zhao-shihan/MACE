#pragma once

#include "TFile.h"

#include "Reconstruction/Global.hh"
#include "Reconstruction/Recognizer/HoughBase.hh"

class MACE::Reconstruction::Recognizer::HoughCartesian final :
    public MACE::Reconstruction::Recognizer::HoughBase {
    HoughCartesian(const HoughCartesian&) = delete;
    HoughCartesian& operator=(const HoughCartesian&) = delete;
public:
    HoughCartesian(Double_t houghSpaceExtent, Eigen::Index size, Double_t protectedRadius);
    ~HoughCartesian();

    void EnableHoughSpaceVisualization(bool val) { fEnableHoughSpaceVis = val; }
    void SaveLastRecognition(const char* fileName) override;

private:
    void HoughTransform() override;

    Double_t ToReal1(Eigen::Index i) const override { return -fExtent + (i + 0.5) * fResolution; }
    Double_t ToReal2(Eigen::Index j) const override { return -fExtent + (j + 0.5) * fResolution; }
    Eigen::Index ToHough1(Double_t x) const override { return (x + fExtent) / fResolution; }
    Eigen::Index ToHough2(Double_t y) const override { return (y + fExtent) / fResolution; }
    Double_t Cross(const CLHEP::Hep3Vector& hitPos, const RealCoordinate& center) const override;

private:
    const Double_t fExtent;
    const Double_t fResolution;
    const Double_t fProtectedRadius;

    bool fEnableHoughSpaceVis = false;
    HoughSpace<size_t> fHoughSpaceVis;

    TFile* fFile = nullptr;
};