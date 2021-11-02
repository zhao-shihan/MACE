#pragma once

#include "TGeoManager.h"

#include "ConstField.h"
#include "RKTrackRep.h"
#include "KalmanFitterRefTrack.h"

#include "Reconstruction/Global.hh"

class MACE::Reconstruction::Fitter::Kalman final {
    Kalman(const Kalman&) = delete;
    Kalman& operator=(const Kalman&) = delete;
private:
    using RecognizedTrack = std::pair<std::vector<std::shared_ptr<const DataModel::Hit::SpectrometerHit>>, std::pair<Double_t, Double_t>>;

public:
    Kalman(const char* gdml);
    ~Kalman();

    void SetMagneticField(Double_t Bz);
    void SetArcResolution(Double_t res) { fArcResolution = res; }
    void SetZResolution(Double_t res) { fZResolution = res; }
    void Fit(const std::vector<RecognizedTrack>& recognized);
    void OpenDisplay() const;

private:
    Double_t fArcResolution = 1.0;
    Double_t fZResolution = 2.0;
    genfit::ConstField* fBField;
    genfit::KalmanFitterRefTrack* fKalmanFitter;
    std::vector<std::shared_ptr<genfit::Track>> fFitted;
};