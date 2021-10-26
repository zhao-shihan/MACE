#pragma once

#include <list>

#include "Eigen/Core"

#include "DataModel/Hit/SpectrometerHit.hh"

#include "Reconstruction/Global.hh"

class MACE::Reconstruction::Recognizer::HoughBase {
    HoughBase(const HoughBase&) = delete;
    HoughBase& operator=(const HoughBase&) = delete;
protected:
    using SpectrometerHitList = std::vector<DataModel::Hit::SpectrometerHit>;
    using SpectrometerHitPointerList = std::vector<const DataModel::Hit::SpectrometerHit*>;
    template<typename T>
    using HoughSpace = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
    using Height_t = Int_t;
    using HoughCoordinate = std::pair<Eigen::Index, Eigen::Index>;
    using RealCoordinate = std::pair<Double_t, Double_t>;
    using CoordinateSet = std::pair<HoughCoordinate, RealCoordinate>;

public:
    HoughBase(Eigen::Index size);
    virtual ~HoughBase();

    void SetHitListToBeRecognized(const SpectrometerHitList* hitList) { fpHitList = hitList; }
    void Recognize();
    const auto& GetRecognizedTrackList() const { return fRecognizedTrackList; }

    virtual void SaveLastRecognition(const char*) { /* no impl */ }

    void SetProtectedRadius(Double_t val) { fProtectedRadius = val; }
    void SetThreshold(Height_t val) { fThreshold = val; }

private:
    void Initialize();
    virtual void HoughTransform() = 0;
    virtual void VoteForCenter() = 0;
    virtual void CenterClusterizaion() = 0;
    virtual void GenerateResult() = 0;

protected:
    const Eigen::Index fSize;
    Double_t fProtectedRadius = 500;
    Height_t fThreshold = 12;

    const SpectrometerHitList* fpHitList = nullptr;
    HoughSpace<SpectrometerHitPointerList> fHoughStore;
    HoughSpace<Height_t> fHoughSpace;
    std::list<CoordinateSet> fCenterCandidateList;
    std::vector<std::vector<HoughCoordinate>> fCenterClusterList;
    std::vector<SpectrometerHitPointerList> fRecognizedTrackList;
};