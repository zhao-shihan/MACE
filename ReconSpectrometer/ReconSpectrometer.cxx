#include "DataModel/PersistencyReader.hxx"
#include "DataModel/PersistencyWriter.hxx"
#include "ReconSpectrometer/Reconstructor/TrueFinder.hxx"
#include "ReconSpectrometer/Reconstructor/Hough.hxx"
#include "ReconSpectrometer/Fitter/Dummy.hxx"
#include "ReconSpectrometer/Fitter/DirectSubSpaceLeastVariance.hxx"

using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

int main(int, char** argv) {
    PersistencyReader reader;
    PersistencyWriter writer;
    reader.Open(argv[1]);
    writer.Open(TString("reconed_") + argv[1]);

    using Hit_t = SpectrometerSimHit;
    using Track_t = HelixTrack;

    // Reconstructor::TrueFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Reconstructor::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Reconstructor::TrueFinder<Fitter::DirectSubSpaceLeastVariance, Hit_t, Track_t> reconstructor;

    std::vector<std::shared_ptr<Track_t>> allTracks(0);
    for (Long64_t i = 0; ; ++i) {
        auto [hitData, tree] = reader.CreateListFromTree<Hit_t>(i);
        if (tree == nullptr) { break; }

        reconstructor.Reconstruct(hitData);
        const auto& reconHits = reconstructor.GetReconstructedHitList();
        const auto& tracks = reconstructor.GetTrackList();

        writer.CreateTreeFromList<Track_t>(tracks, i);
        allTracks.insert(allTracks.cend(), tracks.cbegin(), tracks.cend());
    }

    writer.SetTreeNamePrefixFormat("All_");
    writer.CreateTreeFromList<Track_t>(allTracks);

    writer.WriteTrees();
    writer.Close();
    reader.Close();

    return EXIT_SUCCESS;
}
