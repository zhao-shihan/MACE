#pragma once

#include <list>

#include "Eigen/Core"

#include "DataModel/Hit/SpectrometerHit.hh"
#include "Reconstruction/Global.hh"

class MACE::Reconstruction::Recognizer::HoughBase {
    HoughBase(const HoughBase&) = delete;
    HoughBase& operator=(const HoughBase&) = delete;
protected:
    using Hit = std::shared_ptr<const DataModel::Hit::SpectrometerHit>;

    // I use void* to avoid type self-reference. No elegant methods found so far.
    using HitMapList = std::list<void*>; // Important: const void* == const HitMap*
    using HitMap = std::pair<Hit, std::vector<std::pair<HitMapList*, HitMapList::const_iterator>>>;

    template<typename T>
    using HoughSpace = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
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

    virtual Double_t ToReal1(Eigen::Index i) const = 0;
    virtual Double_t ToReal2(Eigen::Index j) const = 0;
    virtual Eigen::Index ToHough1(Double_t x1) const = 0;
    virtual Eigen::Index ToHough2(Double_t x2) const = 0;
    virtual Double_t Cross(const TEveVectorD& hitPos, const RealCoordinate& center) const = 0;

protected:
    const Eigen::Index fRows;
    const Eigen::Index fCols;
    size_t fThreshold = 12;
    Double_t fTrackTimeWindow = 10.0;

    std::vector<HitMap> fHitStore;
    HoughSpace<HitMapList> fHoughSpace;
    std::vector<std::pair<std::vector<Hit>, RealCoordinate>> fRecognizedList;

private:
    std::vector<std::pair<const HitMapList*, RealCoordinate>> fExceedThreshold;
    std::vector<std::pair<Double_t, std::vector<HitMap*>>> fLeftHandCandidateTrackList;
    std::vector<std::pair<Double_t, std::vector<HitMap*>>> fRightHandCandidateTrackList;
};