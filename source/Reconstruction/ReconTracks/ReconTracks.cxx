#include "Core/DataModel/DataFactory.hxx"
#include "Reconstruction/ReconTracks/Fitter/DirectLeastSquare.hxx"
#include "Reconstruction/ReconTracks/Fitter/Dummy.hxx"
#include "Reconstruction/ReconTracks/Fitter/PerfectFitter.hxx"
#include "Reconstruction/ReconTracks/Tracker/Hough.hxx"
#include "Reconstruction/ReconTracks/Tracker/PerfectFinder.hxx"
#include "Utility/MPITool/MPIFileTools.hxx"
#include "Utility/MPITool/MPIJobsAssigner.hxx"
#include "Utility/PhysicalConstant.hxx"

#include "CLHEP/Random/MTwistEngine.h"
#include "CLHEP/Random/RandGauss.h"

using namespace MACE::Core::DataModel::SimHit;
using namespace MACE::Core::DataModel::Track;
using namespace MACE::Reconstruction::ReconTracks;
using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
using namespace MACE::Utility::MPITool;
using namespace MACE::Utility::PhysicalConstant;

using MACE::Core::DataModel::DataFactory;

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
    Tracker::PerfectFinder<Fitter::DirectLeastSquare, Hit_t, CDCHelixTrack> reconstructor;
    reconstructor.SetThreshold(threshold);
    reconstructor.GetFitter()->SetVerbose(fitterVerbose);
    reconstructor.GetFitter()->SetTolerance(tolerance);
    reconstructor.GetFitter()->SetMaxStepsForNewtonRaphson(maxStepNR);
    reconstructor.GetFitter()->SetMaxStepsForConjugateGrad(maxStepCG);

    Tracker::PerfectFinder<Fitter::PerfectFitter, Hit_t, CDCPhysicsTrack> perfectReconstructor;
    auto&& perfectFitter = *perfectReconstructor.GetFitter();
    perfectReconstructor.SetThreshold(threshold);

    std::filesystem::path outName(nameIn);
    outName.replace_extension("");
    MPIFileTools mpiFileOut(outName.string() + "_recTrk", ".root");
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataFactory dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    auto treeIndexRange = dataHub.GetTreeIndexRange<Hit_t>(fileIn);
    auto [treeBegin, treeEnd] = MPIJobsAssigner(treeIndexRange).GetJobsIndexRange();

    CLHEP::MTwistEngine mtEng;

    std::cout << "Rank" << MPI::COMM_WORLD.Get_rank() << " is ready to process data of repetition " << treeBegin << " to " << treeEnd - 1 << std::endl;

    for (Long64_t treeIndex = treeBegin; treeIndex < treeEnd; ++treeIndex) {
        dataHub.SetPrefixFormatOfTreeName("Rep#_");
        std::cout << "Now processing " << dataHub.GetTreeName<Hit_t>(treeIndex) << " ..." << std::endl;

        auto hitData = dataHub.CreateAndFillList<Hit_t>(fileIn, treeIndex);

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
        std::vector<std::shared_ptr<CDCPhysicsTrack>> physicsTracks;
        physicsTracks.reserve(helixTracks.size());
        for (auto&& track : helixTracks) {
            physicsTracks.emplace_back(std::make_shared<CDCPhysicsTrack>(*track));
        }

        std::vector<std::shared_ptr<CDCPhysicsTrack>> errors;
        errors.reserve(physicsTracks.size());
        for (size_t i = 0; i < physicsTracks.size(); ++i) {
            auto hits = trackedHits[i];
            const auto& physicsTrack = *physicsTracks[i];
            auto& error = *errors.emplace_back(std::make_shared<CDCPhysicsTrack>());
            perfectFitter.Fit(hits, error);
            const auto timeErr = physicsTrack.GetVertexTime() - error.GetVertexTime();
            const auto positionErr = physicsTrack.GetVertexPosition() - error.GetVertexPosition();
            const auto energyErr = physicsTrack.GetVertexEnergy() - error.GetVertexEnergy();
            const auto momentumErr = physicsTrack.GetVertexMomentum() - error.GetVertexMomentum();
            const auto particleErr = error.GetParticle() + '>' + physicsTrack.GetParticle();
            error.SetVertexTime(timeErr);
            error.SetVertexPosition(positionErr);
            error.SetVertexEnergy(energyErr);
            error.SetVertexMomentum(momentumErr);
            error.SetParticle(particleErr);
            error.SetChi2(physicsTrack.GetChi2());
        }

        dataHub.SetPrefixFormatOfTreeName("Rep#_Omitted_");
        dataHub.CreateAndFillTree<Hit_t>(ommitedHits, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Perfect_");
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(perfectTracks, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Exact_");
        dataHub.CreateAndFillTree<CDCHelixTrack>(helixTracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(physicsTracks, treeIndex)->Write();
        dataHub.SetPrefixFormatOfTreeName("Rep#_Error_");
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(errors, treeIndex)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
