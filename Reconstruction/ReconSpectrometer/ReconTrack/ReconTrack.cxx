#include "DataModel/DataHub.hxx"
#include "ReconSpectrometer/ReconTrack/Tracker/TrueFinder.hxx"
#include "ReconSpectrometer/ReconTrack/Tracker/Hough.hxx"
#include "ReconSpectrometer/ReconTrack/Fitter/Dummy.hxx"
#include "ReconSpectrometer/ReconTrack/Fitter/DirectLeastSquare.hxx"
#include "MPITools/MPIFileTools.hxx"

using namespace MACE;
using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

int main(int, char** argv) {
    MPI::Init();

    MPIFileTools mpiFileToolsIn(argv[1], ".root");
    MPIFileTools mpiFileToolsOut(std::string("reconed_") + argv[1], ".root");

    TFile fileIn(mpiFileToolsIn.GetFilePath().c_str(), "read");
    TFile fileOut(mpiFileToolsOut.GetFilePath().c_str(), "recreate");

    using Hit_t = SpectrometerSimHit;
    using Track_t = HelixTrack;

    // Tracker::TrueFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Tracker::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Tracker::TrueFinder<Fitter::DirectLeastSquare, Hit_t, Track_t> reconstructor;
    reconstructor.GetFitter()->SetVerbose(std::stoi(argv[2]));
    reconstructor.GetFitter()->SetTolerance(std::stod(argv[3]));
    reconstructor.GetFitter()->SetMaxSteps(std::stod(argv[4]));

    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");

    for (Long64_t i = 0; ; ++i) {
        auto tree = dataHub.FindTree<Hit_t>(fileIn, i);
        if (tree == nullptr) { break; }
        auto hitData = dataHub.CreateAndFillList<Hit_t>(*tree);

        reconstructor.Reconstruct(hitData);
        // const auto& reconHits = reconstructor.GetReconstructedHitList();
        const auto& tracks = reconstructor.GetTrackList();

        dataHub.CreateAndFillTree<Track_t>(tracks, i)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    mpiFileToolsOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
