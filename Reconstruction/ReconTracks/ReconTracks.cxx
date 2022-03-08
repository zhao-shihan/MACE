#include "DataModel/DataHub.hxx"
#include "ReconTracks/Tracker/PerfectFinder.hxx"
#include "ReconTracks/Tracker/Hough.hxx"
#include "ReconTracks/Fitter/Dummy.hxx"
#include "ReconTracks/Fitter/DirectLeastSquare.hxx"
#include "MPITools/MPIFileTools.hxx"
#include "MPITools/MPIJobsAssigner.hxx"

using namespace MACE;
using namespace MACE::ReconTracks;
using namespace MACE::DataModel;

using Hit_t = SpectrometerSimHit;
using Track_t = HelixTrack;

int main(int, char** argv) {
    MPI::Init();

    // Tracker::PerfectFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Tracker::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Tracker::PerfectFinder<Fitter::DirectLeastSquare, Hit_t, Track_t> reconstructor;
    reconstructor.GetFitter()->SetVerbose(std::stoi(argv[2]));
    reconstructor.GetFitter()->SetTolerance(std::stod(argv[3]));
    reconstructor.GetFitter()->SetMaxSteps(std::stod(argv[4]));

    TFile fileIn(argv[1], "read");

    std::string outName(argv[1]);
    outName.erase(outName.length() - 5);
    MPIFileTools mpiFileOut("reconed_" + outName, ".root");
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    auto treeIndexRange = dataHub.FindTreeIndexRange<Hit_t>(fileIn);
    auto [treeBegin, treeEnd] = MPIJobsAssigner(treeIndexRange).GetJobsIndexRange();

    std::cout << "Rank" << MPI::COMM_WORLD.Get_rank() << " is ready to process data of repetition " << treeBegin << " to " << treeEnd - 1 << std::endl;

    for (Long64_t treeIndex = treeBegin; treeIndex < treeEnd; ++treeIndex) {
        auto tree = dataHub.FindTree<Hit_t>(fileIn, treeIndex);
        auto hitData = dataHub.CreateAndFillList<Hit_t>(*tree);

        reconstructor.Reconstruct(hitData);
        const auto& tracks = reconstructor.GetTrackList();
        const auto& ommitedHits = reconstructor.GetOmittedHitList();

        std::vector<std::shared_ptr<PhysicsTrack>> physicsTracks;
        physicsTracks.reserve(tracks.size());
        for (auto&& track : tracks) {
            physicsTracks.emplace_back(std::make_shared<PhysicsTrack>(*track, 1, 0.1_T));
        }

        dataHub.CreateAndFillTree<Track_t>(tracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<PhysicsTrack>(physicsTracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<Hit_t>(ommitedHits, treeIndex)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
