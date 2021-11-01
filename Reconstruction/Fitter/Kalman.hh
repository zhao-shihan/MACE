/* #pragma once

#include "TGeoManager.h"

#include "ConstField.h"
#include "KalmanFitterRefTrack.h"

#include "Reconstruction/Global.hh"

class MACE::Reconstruction::Fitter::Kalman final {
    Kalman(const Kalman&) = delete;
    Kalman& operator=(const Kalman&) = delete;
private:
    using RecognizedTrack = std::pair<std::vector<std::shared_ptr<const DataModel::Hit::SpectrometerHit>>, std::pair<Double_t, Double_t>>;

public:
    Kalman();
    ~Kalman();

    // void SetGeometry(const char* gdml) { fGeoManager->Import(gdml); }
    void SetRecognizedToBeFit(const std::vector<RecognizedTrack>& recgzed) { fpRecognized = &recgzed; }
    void SetMagneticField(Double_t val);
    void Fit();

private:
    void Initialize();
    void DoFit();

private:
    const std::vector<RecognizedTrack>* fpRecognized = nullptr;
    genfit::ConstField* fBField;
    // TGeoManager* fGeoManager;
    genfit::KalmanFitterRefTrack* fKalmanFitter;
    std::vector<std::shared_ptr<genfit::Track>> fFitted;
}; */