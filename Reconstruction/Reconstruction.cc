#include "TH2I.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMarker.h"
#include "TEllipse.h"
#include "TDirectory.h"

#include "DataModel/PersistencyReader.hh"
#include "Reconstruction/Recognizer/HoughCartesian.hh"
#include "Reconstruction/Recognizer/HoughPolar.hh"
#include "Reconstruction/Fitter/Kalman.hh"

using namespace MACE;

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
    DataModel::PersistencyReader reader(argv[1]);
    Reconstruction::Recognizer::HoughCartesian recognizer(2500, std::stol(argv[2]), 500);
    // Reconstruction::Recognizer::HoughPolar recognizer(350, 5000, std::stol(argv[2]), std::stol(argv[3]));
    recognizer.EnableHoughSpaceVisualization(true);
    auto hitList = reader.CreateListFromTree<DataModel::Hit::SpectrometerHit>();
    recognizer.SetEventToBeRecognized(hitList);
    recognizer.Recognize();
    const auto& recognized = recognizer.GetRecognizedTrackList();
    recognizer.SaveLastRecognition("recognition.root");
    reader.Close();

    Reconstruction::Fitter::Kalman fitter("MACEGeometry.gdml");
    fitter.Fit(recognized);
    fitter.OpenDisplay();
}