#pragma once

#include "Eigen/Core"

#include "DataModel/Hit/SpectrometerHit.hh"
#include "Reconstruction/Global.hh"

template<class SpectrometerHitType>
class MACE::Reconstruction::Recognizer::HoughBase {
    static_assert(std::is_base_of_v<DataModel::SpectrometerHit, SpectrometerHitType>,
        "SpectrometerHitType should be derived from MACE::DataModel::Hit::SpectrometerHit");

    HoughBase(const HoughBase&) = delete;
    HoughBase& operator=(const HoughBase&) = delete;

protected:
    using Hit = std::shared_ptr<const SpectrometerHitType>;

    using HitList = std::vector<const Hit*>;

    using HoughSpace = Eigen::Matrix<HitList, Eigen::Dynamic, Eigen::Dynamic>;
    using HoughCoordinate = std::pair<Eigen::Index, Eigen::Index>;
    using RealCoordinate = std::pair<Double_t, Double_t>;

public:
    HoughBase(Eigen::Index rows, Eigen::Index cols);
    virtual ~HoughBase();

    void SetThreshold(size_t threshold) { fThreshold = threshold; }
    void SetTrackTimeWindow(Double_t time) { fTrackTimeWindow = time; }

    void SetEventToBeRecognized(const std::vector<Hit>& hitVector);
    void Recognize();
    const auto& GetRecognizedTrackList() const { return fRecognizedList; }

    virtual void SaveLastRecognition(const char*) { /* no impl */ }

private:
    void Initialize();
    virtual void HoughTransform() = 0;
    void FindExceedThreshold();
    void GenerateResult();

    virtual RealCoordinate ToRealCartesian(const HoughCoordinate& center) const = 0;

    size_t EffectiveSizeOf(const HitList* hitList) { return std::count_if(hitList->begin(), hitList->end(), [](auto hit) { *hit != nullptr; }); }

protected:
    const Eigen::Index fRows;
    const Eigen::Index fCols;
    size_t fThreshold = 12;
    Double_t fTrackTimeWindow = 500.0;

    std::vector<Hit> fHitStore;
    HoughSpace fHoughSpace;
    std::vector<std::pair<std::vector<Hit>, RealCoordinate>> fRecognizedList;

private:
    std::vector<std::pair<const HitList*, RealCoordinate>> fExceedThreshold;
    std::vector<std::pair<Double_t, std::vector<const Hit*>>> fLeftHandCandidateTrackList;
    std::vector<std::pair<Double_t, std::vector<const Hit*>>> fRightHandCandidateTrackList;
};

#include "Reconstruction/Recognizer/HoughBase.icc"