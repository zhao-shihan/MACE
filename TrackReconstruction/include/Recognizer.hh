#pragma once

#include "Eigen/Core"

#include "TrackReconstructionGlobal.hh"

class MACE::TrackReconstruction::Recognizer final {
    MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(Recognizer);
private:
    template<typename T> using HoughSpace = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
    using HoughCount_t = Int_t;

public:
    Recognizer(Eigen::Index size);

    void SetPluseData(const PluseData& pluseData) { fpPluseData = &pluseData; fDataResultIsConsistent = false; }
    void Recognize();
    const HitPointerList& GetResult() const { return fResult; }
    void PrintLastRecognition(const char* realSpaceGraphFileName, const char* houghSpaceGraphFileName, UInt_t graphWidth = 680, UInt_t graphHeight = 480) const;

    void SetThreshold(HoughCount_t val) { fThreshold = val; }
    void SetMaxRadius(Double_t val) { fMaxRadius = val; }
    void SetProtectedRadius(Double_t val) { fProtectedRadius = val; }
    void SetCoincidenceChamberID(Int_t val) { fCoincidenceChamberID = val; }

private:
    void Initialize();
    void HoughTransform();
    void GenerateResult();

private:
    HoughCount_t fThreshold = 5;
    Double_t fMaxRadius = 2000;
    Double_t fProtectedRadius = 200;
    Int_t fCoincidenceChamberID = 3;

    bool fDataResultIsConsistent = false;

    const PluseData* fpPluseData = nullptr;
    const Eigen::Index fSize;
    HoughSpace<HitPointerList> fHoughStore;
    HoughSpace<HoughCount_t> fHoughCount;
    HitPointerList fResult;
};