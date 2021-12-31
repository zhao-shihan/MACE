#include "FieldManager.h"
#include "MaterialEffects.h"
#include "TGeoMaterialInterface.h"
#include "Track.h"
#include "SpacepointMeasurement.h"
#include "EventDisplay.h"

#include "Reconstruction/Fitter/Kalman.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"

using namespace MACE::Reconstruction::Fitter;

template<class SpectrometerHitType>
Kalman<SpectrometerHitType>::Kalman(const char* gdml) :
    fBField(new genfit::ConstField(0.0, 0.0, 0.1)),
    fKalmanFitter(new genfit::KalmanFitterRefTrack()),
    fFitted(0) {
    new TGeoManager("Geom", "detector geometry");
    TGeoManager::Import(gdml);
    genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());
    genfit::FieldManager::getInstance()->init(fBField);
}

template<class SpectrometerHitType>
Kalman<SpectrometerHitType>::~Kalman() {
    // delete fGeoManager;
    delete fBField;
    delete fKalmanFitter;
    genfit::FieldManager::getInstance()->destruct();
}

template<class SpectrometerHitType>
void Kalman<SpectrometerHitType>::SetMagneticField(Double_t Bz) {
    delete fBField;
    fBField = new genfit::ConstField(0.0, 0.0, Bz);
    genfit::FieldManager::getInstance()->init(fBField);
}

template<class SpectrometerHitType>
void Kalman<SpectrometerHitType>::Fit(const std::vector<RecognizedTrack>& recognized) {
    fFitted.clear();
    fFitted.reserve(recognized.size());

    std::vector<genfit::TrackPoint*> trackPointList(0);
    TMatrixDSym hitCov(3);
    hitCov.Zero();
    Int_t hitID = 0;

    for (auto&& [recognizedTrack, center] : recognized) {
        trackPointList.reserve(recognizedTrack.size());

        const auto& firstHitPos = std::min_element(recognizedTrack.cbegin(), recognizedTrack.cend(),
            [](const auto& hit1, const auto& hit2)->bool {
                return hit1->GetCellID() < hit2->GetCellID();
            }
        )->get()->GetWirePosition();
        auto hitCrossCenter = firstHitPos.fX * center.second - center.first * firstHitPos.fY;
        auto pdgCode = (hitCrossCenter > 0) ? (11) : (-11); // cross>0 => e-(11), cross<0 => e+(-11)
        const auto& track = fFitted.emplace_back(std::make_shared<genfit::Track>(new genfit::RKTrackRep(pdgCode), TVector3(0.0, 0.0, 0.0), TVector3(firstHitPos)));

        for (auto&& hit : recognizedTrack) {
            const auto& hitPos = hit->GetWirePosition();

            auto hitR = hitPos.Mag();
            auto resX = -(hitPos.fY / hitR) * fArcResolution;
            auto resY = (hitPos.fX / hitR) * fArcResolution;
            auto resZ = fZResolution;
            hitCov(0, 0) = resX * resX;
            hitCov(1, 1) = resY * resY;
            hitCov(2, 2) = resZ * resZ;

            auto measurement = new genfit::SpacepointMeasurement(TVectorD(3, hitPos), hitCov, hit->GetCellID(), hitID, nullptr);
            trackPointList.emplace_back(new genfit::TrackPoint(measurement, track.get()));

            ++hitID;
        }

        track->insertPoints(trackPointList);
        track->checkConsistency();
        fKalmanFitter->processTrack(track.get());
        track->checkConsistency();

        trackPointList.clear();
    }
}

template<class SpectrometerHitType>
void Kalman<SpectrometerHitType>::OpenDisplay() const {
    auto display = genfit::EventDisplay::getInstance();
    for (auto&& track : fFitted) {
        display->addEvent(track.get());
    }
    display->open();
    display->reset();
}