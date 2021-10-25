#pragma once

#include <list>

#include "Eigen/Core"

#include "TFile.h"
#include "TVector2.h"

#include "DataModel/Hit/SpectrometerHit.hh"

#include "Reconstruction/Global.hh"

class MACE::Reconstruction::Recognizer final {
    Recognizer(const Recognizer&) = delete;
    Recognizer& operator=(const Recognizer&) = delete;
private:
    using SpectrometerHitList = std::vector<DataModel::Hit::SpectrometerHit>;
    using SpectrometerHitPointerList = std::vector<const DataModel::Hit::SpectrometerHit*>;
    template<typename T>
    using HoughSpace = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
    using Height_t = Int_t;
    using HoughPoint = std::pair<Eigen::Index, Eigen::Index>;
    using RealPoint = std::pair<Double_t, Double_t>;
    using RealPointPolar = std::pair<Double_t, Double_t>;

public:
    Recognizer(Double_t houghSpaceExtent, Double_t proposingHoughSpaceResolution);
    ~Recognizer();

    void SetHitListToBeRecognized(const SpectrometerHitList* hitList) { fpHitList = hitList; }
    void Recognize();
    const auto& GetRecognizedTrackList() const { return fRecognizedTrackList; }

    void SaveLastRecognition(const char* fileName);

    void SetProtectedRadius(Double_t val) { fProtectedRadius = val; }
    void SetThreshold(Height_t val) { fThreshold = val; }
    void SetHoughClusterScannerRadialExtent(Double_t val) { fScannerDR = 0.5 * val; }
    void SetHoughClusterScannerAngularExtent(Double_t val) { fScannerDPhi = 0.5 * val; }

private:
    void Initialize();
    void HoughTransform();
    void VoteForCenter();
    void CenterClusterizaion();
    void GenerateResult();

    void ClusterizationImpl(std::list<std::pair<HoughPoint, RealPointPolar>>::const_iterator candidate, std::vector<HoughPoint>& cluster);

    Double_t ToRealX(Eigen::Index i) const { return -fExtent + (i + 0.5) * fResolution; }
    Double_t ToRealY(Eigen::Index j) const { return -fExtent + (j + 0.5) * fResolution; }
    Eigen::Index ToHoughX(Double_t x) const { return (x + fExtent) / fResolution; }
    Eigen::Index ToHoughY(Double_t y) const { return (y + fExtent) / fResolution; }

private:
    const Eigen::Index fSize;
    const Double_t fExtent;
    const Double_t fResolution;
    Double_t fProtectedRadius = 500;
    Height_t fThreshold = 12;
    Double_t fScannerDR = 100;
    Double_t fScannerDPhi = M_PI / 180;

    const SpectrometerHitList* fpHitList = nullptr;
    HoughSpace<SpectrometerHitPointerList> fHoughStore;
    HoughSpace<Height_t> fHoughSpace;
    std::list<std::pair<HoughPoint, RealPointPolar>> fCenterCandidateList;
    std::vector<std::vector<HoughPoint>> fCenterClusterList;
    std::vector<SpectrometerHitPointerList> fRecognizedTrackList;

    TFile* fFile = nullptr;
};