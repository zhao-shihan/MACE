/* #include "FieldManager.h"
#include "Track.h"
#include "SpacepointMeasurement.h"

#include "Reconstruction/Fitter/Kalman.hh"
#include "DataModel/Hit/SpectrometerHit.hh"

using namespace MACE::Reconstruction::Fitter;

Kalman::Kalman() :
    fBField(new genfit::ConstField(0.0, 0.0, 0.1)),
    // fGeoManager(new TGeoManager("FitterGeom", "detector geometry")),
    fKalmanFitter(new genfit::KalmanFitterRefTrack()) {
    genfit::FieldManager::getInstance()->init(fBField);
}

Kalman::~Kalman() {
    // delete fGeoManager;
    delete fBField;
    delete fKalmanFitter;
    genfit::FieldManager::getInstance()->destruct();
}

void Kalman::SetMagneticField(Double_t val) {
    delete fBField;
    fBField = new genfit::ConstField(0.0, 0.0, 0.1);
    genfit::FieldManager::getInstance()->init(fBField);
}

void Kalman::Fit() {
    Initialize();
    DoFit();
}

void Kalman::Initialize() {
    fFitted.clear();
    fFitted.reserve(fpRecognized->size());
}

void Kalman::DoFit() {
    std::vector<genfit::TrackPoint*> points(0);
    for (auto&& [recognizedTrack, center] : *fpRecognized) {
        points.reserve(recognizedTrack.size());
        auto& track = fFitted.emplace_back(std::make_shared<genfit::Track>());
        for (auto&& hit : recognizedTrack) {
            auto measurement = new genfit::SpacepointMeasurement(
                TVectorD(3, hit->GetHitPosition().Arr()),);
            points.emplace_back();
        }

        track->insertPoints(points);
        points.clear();
    }
} */