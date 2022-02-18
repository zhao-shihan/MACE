#include "DataModel/DataHub.hxx"
#include "ReconSpectrometer/Reconstructor/TrueFinder.hxx"
#include "ReconSpectrometer/Reconstructor/Hough.hxx"
#include "ReconSpectrometer/Fitter/Dummy.hxx"
#include "ReconSpectrometer/Fitter/DirectSubSpaceLeastVariance.hxx"

using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

int main(int, char** argv) {
    TFile fileIn(argv[1], "read");
    TFile fileOut(TString("reconed_") + argv[1], "recreate");

    using Hit_t = SpectrometerSimHit;
    using Track_t = HelixTrack;

    // Reconstructor::TrueFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Reconstructor::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Reconstructor::TrueFinder<Fitter::DirectSubSpaceLeastVariance, Hit_t, Track_t> reconstructor;

    DataHub dataHub;
    std::vector<std::shared_ptr<Track_t>> allTracks(0);
    for (Long64_t i = 0; ; ++i) {
        auto tree = dataHub.FindTree<Hit_t>(fileIn, i);
        if (tree == nullptr) { break; }
        auto hitData = dataHub.CreateList<Hit_t>(tree);

        reconstructor.Reconstruct(hitData);
        const auto& reconHits = reconstructor.GetReconstructedHitList();
        const auto& tracks = reconstructor.GetTrackList();

        dataHub.CreateTree(tracks, i)->Write();
        allTracks.insert(allTracks.cend(), tracks.cbegin(), tracks.cend());
    }

    dataHub.SetPrefixFormatOfTreeName("All_");
    dataHub.CreateTree(allTracks)->Write();

    fileOut.Close();
    fileIn.Close();

    return EXIT_SUCCESS;
}
