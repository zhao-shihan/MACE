#include <unordered_map>
#include <iostream>

#include "TH2I.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "DataModel/PersistencyReader.hxx"
#include "DataModel/PersistencyWriter.hxx"
#include "DataModel/SimHit/SpectrometerSimHit.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "ReconSpectrometer/Reconstructor/TrueFinder.hxx"
#include "ReconSpectrometer/Reconstructor/Hough.hxx"
#include "ReconSpectrometer/Fitter/Dummy.hxx"
#include "ReconSpectrometer/Fitter/DirectLeastChiSquare.hxx"

using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

int main(int, char** argv) {
    using Hit_t = SpectrometerSimHit;
    using Track_t = HelixTrack;

    PersistencyReader reader(argv[1]);
    Reconstructor::TrueFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Reconstructor::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    auto event = reader.CreateListFromTree<Hit_t>();
    reader.Close();

    reconstructor.Reconstruct(event);
    const auto& reconHits = reconstructor.GetReconstructedHitList();
    const auto& tracks = reconstructor.GetTrackList();

    PersistencyWriter writer(TString("reconed_") + argv[1]);
    writer.CreateTreeFromList<Track_t>(tracks);
    for (auto&& hitList : reconHits) {
        writer.CreateTreeFromList<Hit_t>(hitList);
        writer.NextTree();
    }
    writer.WriteTrees();
    writer.Close();

    return EXIT_SUCCESS;
}