#pragma once

#include "Eigen/Core"

#include "TFile.h"

#include "ReconstructionGlobal.hh"

class MACE::Reconstruction::Recognizer final {
    MACE_TRACK_RECONSTRUCTION_NOT_ALLOW_TO_COPY_BUT_ALLOW_TO_MOVE(Recognizer);
private:
    template<typename T> using HoughSpace = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
    using HoughCount_t = Int_t;

public:
    Recognizer(Double_t houghSpaceExtent, Double_t proposingHoughSpaceResolution);
    ~Recognizer();

    void Recognize(const PluseData& pluseData);
    const auto& GetResult() const { return fResult; }

    void SaveLastRecognition(const char* fileName);

    void SetProtectedRadius(Double_t val) { fProtectedRadius = val; }
    void SetThreshold(HoughCount_t val) { fThreshold = val; }
    // void SetCoincidenceChamberID(Int_t val) { fCoincidenceChamberID = val; }

private:
    void Initialize();
    void HoughTransform();
    void GenerateResult();

private:
    const Eigen::Index fSize;
    const Double_t fExtent;
    const Double_t fResolution;
    Double_t fProtectedRadius = 200;
    HoughCount_t fThreshold = 10;
    Int_t fCoincidenceChamberID = 0;

    const PluseData* fpPluseData = nullptr;
    HoughSpace<HitPointerList> fHoughSpace;
    HitPointerList fResult;

    TFile* fFile = nullptr;
};