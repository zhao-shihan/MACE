#include "DataModel/DataHub.hxx"
#include "ReconSpectrometer/ReconTrack/Tracker/TrueFinder.hxx"
#include "ReconSpectrometer/ReconTrack/Tracker/Hough.hxx"
#include "ReconSpectrometer/ReconTrack/Fitter/Dummy.hxx"
#include "ReconSpectrometer/ReconTrack/Fitter/DirectLeastSquare.hxx"
#include "MPITools/MPIFileTools.hxx"
#include "MPITools/MPIJobsAssigner.hxx"

using namespace MACE;
using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

using Hit_t = SpectrometerSimHit;
using Track_t = HelixTrack;

int main(int, char** argv) {
    MPI::Init();

    // Tracker::TrueFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Tracker::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Tracker::TrueFinder<Fitter::DirectLeastSquare, Hit_t, Track_t> reconstructor;
    reconstructor.GetFitter()->SetVerbose(std::stoi(argv[2]));
    reconstructor.GetFitter()->SetTolerance(std::stod(argv[3]));
    reconstructor.GetFitter()->SetMaxSteps(std::stod(argv[4]));

    TFile fileIn(argv[1], "read");

    std::string outName(argv[1]);
    outName.erase(outName.find_last_of(".root"));
    MPIFileTools mpiFileOut("reconed_" + outName, ".root");
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    auto treeIndexRange = dataHub.FindTreeIndexRange<Hit_t>(fileIn);
    auto [treeBegin, treeEnd] = MPIJobsAssigner(treeIndexRange).GetJobsIndexRange();

    for (Long64_t treeIndex = treeBegin; treeIndex < treeEnd; ++treeIndex) {
        auto tree = dataHub.FindTree<Hit_t>(fileIn, treeIndex);
        auto hitData = dataHub.CreateAndFillList<Hit_t>(*tree);

        reconstructor.Reconstruct(hitData);
        const auto& tracks = reconstructor.GetTrackList();
        const auto& ommitedHits = reconstructor.GetOmittedHitList();

        dataHub.CreateAndFillTree<Track_t>(tracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<Hit_t>(ommitedHits, treeIndex)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
