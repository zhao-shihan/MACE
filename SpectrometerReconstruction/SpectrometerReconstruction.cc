#include "TVector3.h"
#include "TFile.h"
#include "TTreeReader.h"

using HitList = std::list<TVector3>;

std::vector<HitList> ReadData(const char* fileName) {
    auto file = new TFile(fileName, "READ");
    if (!file->IsOpen()) { return std::vector<HitList>(); }

    TTreeReader reader("Spectrometer", file);
    TTreeReaderValue<Int_t>   pluseID(reader, "PluseID");
    TTreeReaderValue<Float_t> hitPositionX(reader, "HitPositionX");
    TTreeReaderValue<Float_t> hitPositionY(reader, "HitPositionY");
    TTreeReaderValue<Float_t> hitPositionZ(reader, "HitPositionZ");

    std::vector<HitList> hitDataList(0);
    std::vector<HitList>::reverse_iterator thisData;
    Int_t thisPluse = -1;
    while (reader.Next()) {
        if (thisPluse != *pluseID) {
            hitDataList.emplace_back(0);
            thisData = hitDataList.rbegin();
            thisPluse = *pluseID;
        }
        thisData->emplace_back(*hitPositionX, *hitPositionY, *hitPositionZ);
    }

    file->Close();
    delete file;

    return hitDataList;
}

#include "Eigen/Core"
#include "TH2I.h"
#include "TCanvas.h"

// using InitialValue = std::pair<TVector3, TVector3>;
using HitPointerList = std::vector<const TVector3*>;
// using RawTrack = std::pair<InitialValue, HitPointerList>;

HitPointerList Hough(const HitList& hitList) {
    constexpr      int threshold = 5;
    constexpr Double_t   xExtent = 10000;
    constexpr      int     xSize = 100;
    constexpr Double_t   yExtent = 10000;
    constexpr      int     ySize = 100;
    constexpr Double_t spectrometerFirstLayerRadius = 90;
    constexpr Double_t yResolution = yExtent / ySize;
    constexpr Double_t xResolution = xExtent / xSize;
    using HoughSpace = Eigen::Matrix<HitPointerList, Eigen::Dynamic, Eigen::Dynamic>;
    using HoughSizeSpace = Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>;

    if (hitList.size() < threshold) { return HitPointerList(0); }

    HoughSpace     hough(xSize, ySize);
    HoughSizeSpace houghSize(xSize, ySize);
    for (int i = 0; i < xSize; ++i) {
        for (int j = 0; j < ySize; ++j) {
            hough(i, j).reserve(10);
            houghSize(i, j) = 0;
        }
    }

    for (const auto& hit : hitList) {
        const Double_t R2 = hit.x() * hit.x() + hit.y() * hit.y();
        const Double_t X = 2.0 * hit.x() / R2;
        const Double_t Y = 2.0 * hit.y() / R2;

        if (fabs(X / Y) < 1.0) {
            for (int i = 0; i < xSize; ++i) {
                const Double_t xc = (-xExtent / 2.0) + (i + 0.5) * xResolution;
                const Double_t yc = (1.0 - X * xc) / Y;
                if (xc * xc + yc * yc < 3 * spectrometerFirstLayerRadius * 3 * spectrometerFirstLayerRadius) { continue; }
                const int j = yc / yResolution + (yExtent / (2.0 * yResolution));
                if (0 <= j && j < ySize) {
                    hough(i, j).push_back(&hit);
                    ++houghSize(i, j);
                }
            }
        } else {
            for (int j = 0; j < ySize; ++j) {
                const Double_t yc = (-yExtent / 2.0) + (j + 0.5) * yResolution;
                const Double_t xc = (1.0 - Y * yc) / X;
                if (xc * xc + yc * yc < 3 * spectrometerFirstLayerRadius * 3 * spectrometerFirstLayerRadius) { continue; }
                const int i = xc / xResolution + (xExtent / (2.0 * xResolution));
                if (0 <= i && i < xSize) {
                    hough(i, j).push_back(&hit);
                    ++houghSize(i, j);
                }
            }
        }
    }

    // TCanvas vis;
    // TH2I h("h2", "hough space", xSize, 0, xSize, ySize, 0, ySize);
    // for (int i = 0; i < xSize; ++i) {
    //     for (int j = 0; j < ySize; ++j) {
    //         h.Fill(i, j, houghSize(i, j));
    //     }
    // }
    // h.Draw("COL");
    // vis.Print("houghSpace.png");

    HitPointerList firstHitList(0);
    int imax, jmax;
    while (houghSize.maxCoeff(&imax, &jmax) >= threshold) {
        houghSize(imax, jmax) = 0;
        const auto* firstHit = *std::min_element(hough(imax, jmax).begin(), hough(imax, jmax).end(), [](const TVector3* r1, const TVector3* r2)->bool { return r1->Mag2() < r2->Mag2(); });
        if (std::find(firstHitList.begin(), firstHitList.end(), firstHit) == firstHitList.end()) {
            if (firstHit->x() * firstHit->x() + firstHit->y() * firstHit->y() < spectrometerFirstLayerRadius * spectrometerFirstLayerRadius) {
                firstHitList.push_back(firstHit);
            }
        }
    }

    // std::cout << hitList.size() << '\t' << firstHitList.size() << std::endl;

    return firstHitList;
}


#include "ConstField.h"
#include "Exception.h"
#include "FieldManager.h"
#include "KalmanFitterRefTrack.h"
#include "StateOnPlane.h"
#include "Track.h"
#include "TrackPoint.h"

#include "MaterialEffects.h"
#include "RKTrackRep.h"
#include "TGeoMaterialInterface.h"

#include "EventDisplay.h"

#include "PlanarMeasurement.h"

#include "TEveManager.h"
#include "TGeoManager.h"

#include "TDatabasePDG.h"
#include "TMath.h"

int main(int, char** argv) {
    auto data = ReadData(argv[1]);
    for (const auto& hitList : data) {
        Hough(hitList);
    }

    /*
    // init geometry and mag. field
    // new TGeoManager("Geometry", "Geane geometry");
    // TGeoManager::Import("genfitGeom.root");
    genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());
    genfit::FieldManager::getInstance()->init(new genfit::ConstField(0., 1, 0)); // 1 T


    // init event display
    genfit::EventDisplay* display = genfit::EventDisplay::getInstance();


    // init fitter
    genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack();


    // particle pdg code; pion hypothesis
    const int pdg = 211;

    // start values for the fit, e.g. from pattern recognition
    TVector3 pos(0, 0, 0);
    TVector3 mom(0, 0, 3);


    // trackrep
    genfit::AbsTrackRep* rep = new genfit::RKTrackRep(pdg);

    // create track
    genfit::Track fitTrack(rep, pos, mom);


    const int detId(0); // detector ID
    int planeId(0); // detector plane ID
    int hitId(0); // hit ID

    double detectorResolution(0.001); // resolution of planar detectors
    TMatrixDSym hitCov(2);
    hitCov.UnitMatrix();
    hitCov *= detectorResolution * detectorResolution;


    // add some planar hits to track with coordinates I just made up
    TVectorD hitCoords(2);
    hitCoords[0] = 0;
    hitCoords[1] = 0;
    genfit::PlanarMeasurement* measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
    measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0, 0, 0), TVector3(1, 0, 0), TVector3(0, 1, 0))), ++planeId);
    fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

    hitCoords[0] = -0.15;
    hitCoords[1] = 0;
    measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
    measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0, 1, 5), TVector3(1, 0, 0), TVector3(0, 1, 0))), ++planeId);
    fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

    hitCoords[0] = -0.15;
    hitCoords[1] = 0;
    measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
    measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0, 2, 10), TVector3(1, 0, 0), TVector3(0, 1, 0))), ++planeId);
    fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

    hitCoords[0] = -0.15;
    hitCoords[1] = 0;
    measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
    measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0, 1, 15), TVector3(1, 0, 0), TVector3(0, 1, 0))), ++planeId);
    fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));

    hitCoords[0] = -0.4;
    hitCoords[1] = 0;
    measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, detId, ++hitId, nullptr);
    measurement->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(TVector3(0, 0, 20), TVector3(1, 0, 0), TVector3(0, 1, 0))), ++planeId);
    fitTrack.insertPoint(new genfit::TrackPoint(measurement, &fitTrack));



    //check
    fitTrack.checkConsistency();

    // do the fit
    fitter->processTrack(&fitTrack);

    // print fit result
    fitTrack.getFittedState().Print();

    //check
    fitTrack.checkConsistency();


    display->addEvent(&fitTrack);


    delete fitter;

    // open event display
    display->open(); */
}