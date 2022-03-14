#include "CLHEP/Units/PhysicalConstants.h"
#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Random/MTwistEngine.h"

#include "DataModel/DataHub.hxx"
#include "ReconTracks/Tracker/PerfectFinder.hxx"
#include "ReconTracks/Tracker/Hough.hxx"
#include "ReconTracks/Fitter/DirectLeastSquare.hxx"
#include "ReconTracks/Fitter/Dummy.hxx"
#include "ReconTracks/Fitter/PerfectFitter.hxx"
#include "MPITools/MPIFileTools.hxx"
#include "MPITools/MPIJobsAssigner.hxx"

using namespace MACE;
using namespace MACE::ReconTracks;
using namespace MACE::DataModel;

using Hit_t = SpectrometerSimHit;

int main(int, char** argv) {
    MPI::Init();

    const char* nameIn = argv[1];
    const auto threshold = std::stoi(argv[2]);
    const auto fitterVerbose = std::stoi(argv[3]);
    const auto tolerance = std::stod(argv[4]);
    const auto maxStepNR = std::stod(argv[5]);
    const auto maxStepCG = std::stod(argv[6]);
    const auto deltaD = std::stod(argv[7]);
    const auto deltaZ = std::stod(argv[8]);

    TFile fileIn(nameIn, "read");

    // Tracker::PerfectFinder<Fitter::Dummy, Hit_t, Track_t> reconstructor;
    // Tracker::Hough<Fitter::Dummy, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    Tracker::PerfectFinder<Fitter::DirectLeastSquare, Hit_t, HelixTrack> reconstructor;
    reconstructor.SetThreshold(threshold);
    reconstructor.GetFitter()->SetVerbose(fitterVerbose);
    reconstructor.GetFitter()->SetTolerance(tolerance);
    reconstructor.GetFitter()->SetMaxStepsForNewtonRaphson(maxStepNR);
    reconstructor.GetFitter()->SetMaxStepsForConjugateGrad(maxStepCG);

    Tracker::PerfectFinder<Fitter::PerfectFitter, Hit_t, PhysicsTrack> perfectReconstructor;
    auto&& perfectFitter = *perfectReconstructor.GetFitter();
    perfectReconstructor.SetThreshold(threshold);

    std::string outName(nameIn);
    outName.erase(outName.length() - 5);
    MPIFileTools mpiFileOut(outName + "_rec", ".root");
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    auto treeIndexRange = dataHub.GetTreeIndexRange<Hit_t>(fileIn);
    auto [treeBegin, treeEnd] = MPIJobsAssigner(treeIndexRange).GetJobsIndexRange();

    CLHEP::MTwistEngine mtEng;

    std::cout << "Rank" << MPI::COMM_WORLD.Get_rank() << " is ready to process data of repetition " << treeBegin << " to " << treeEnd - 1 << std::endl;

    for (Long64_t treeIndex = treeBegin; treeIndex < treeEnd; ++treeIndex) {
        dataHub.SetPrefixFormatOfTreeName("Rep#_");
        std::cout << "Now processing " << dataHub.GetTreeName<Hit_t>(treeIndex) << " ..." << std::endl;

        auto tree = dataHub.GetTree<Hit_t>(fileIn, treeIndex);
        auto hitData = dataHub.CreateAndFillList<Hit_t>(*tree);

        if (deltaD > 0) {
            for (auto&& hit : hitData) {
                hit->SetDriftDistanceVariance(deltaD);
                const auto smearD = CLHEP::RandGauss::shoot(std::addressof(mtEng), 0, deltaD);
                hit->SetDriftDistance(smearD + hit->GetDriftDistance());
            }
        }
        if (deltaZ > 0) {
            for (auto&& hit : hitData) {
                hit->SetHitPositionZVariance(deltaZ);
                const auto smearZ = CLHEP::RandGauss::shoot(std::addressof(mtEng), 0, deltaZ);
                hit->SetHitPositionZ(smearZ + hit->GetHitPositionZ());
            }
        }

        perfectReconstructor.Reconstruct(hitData);
        const auto& perfectTracks = perfectReconstructor.GetTrackList();

        reconstructor.Reconstruct(hitData);
        const auto& helixTracks = reconstructor.GetTrackList();
        const auto& trackedHits = reconstructor.GetTrackedHitList();
        const auto& ommitedHits = reconstructor.GetOmittedHitList();
        std::vector<std::shared_ptr<PhysicsTrack>> physicsTracks;
        physicsTracks.reserve(helixTracks.size());
        for (auto&& track : helixTracks) {
            physicsTracks.emplace_back(std::make_shared<PhysicsTrack>(*track, 1, 0.1_T, CLHEP::electron_mass_c2));
        }

        std::vector<std::shared_ptr<PhysicsTrack>> errors;
        errors.reserve(physicsTracks.size());
        for (size_t i = 0; i < physicsTracks.size(); ++i) {
            auto hits = trackedHits[i];
            const auto& physicsTrack = *physicsTracks[i];
            auto& error = *errors.emplace_back(std::make_shared<PhysicsTrack>());
            perfectFitter.Fit(hits, error);
            const auto timeErr = physicsTrack.GetVertexTime() - error.GetVertexTime();
            const auto positionErr = physicsTrack.GetVertexPosition() - error.GetVertexPosition();
            const auto energyErr = physicsTrack.GetVertexEnergy() - error.GetVertexEnergy();
            const auto momentumErr = physicsTrack.GetVertexMomentum() - error.GetVertexMomentum();
            const auto chargeErr = physicsTrack.GetCharge() - error.GetCharge();
            error.SetVertexTime(timeErr);
            error.SetVertexPosition(positionErr);
            error.SetVertexEnergy(energyErr);
            error.SetVertexMomentum(momentumErr);
            error.SetCharge(chargeErr);
            error.SetChi2(physicsTrack.GetChi2());
        }

        dataHub.SetPrefixFormatOfTreeName("Rep#_Omitted_");
        dataHub.CreateAndFillTree<Hit_t>(ommitedHits, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Perfect_");
        dataHub.CreateAndFillTree<PhysicsTrack>(perfectTracks, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Exact_");
        dataHub.CreateAndFillTree<HelixTrack>(helixTracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<PhysicsTrack>(physicsTracks, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Error_");
        dataHub.CreateAndFillTree<PhysicsTrack>(errors, treeIndex)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
