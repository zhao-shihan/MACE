#include "MACE/Core/DataFactory.hxx"
#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/ReconTracks/Fitter/DirectLeastSquare.hxx"
#include "MACE/ReconTracks/Fitter/Dummy.hxx"
#include "MACE/ReconTracks/Fitter/PerfectFitter.hxx"
#include "MACE/ReconTracks/Tracker/Hough.hxx"
#include "MACE/ReconTracks/Tracker/PerfectFinder.hxx"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "CLHEP/Random/MTwistEngine.h"
#include "CLHEP/Random/RandGauss.h"

#include <filesystem>

using namespace MACE::Core::DataModel::SimHit;
using namespace MACE::Core::DataModel::Track;
using namespace MACE::ReconTracks;
using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
using namespace MACE::Utility::MPIUtil;
using namespace MACE::Utility::PhysicalConstant;

using MACE::Core::DataFactory;
using MACE::Environment::MPIEnvironment;

using Hit_t = CDCSimHit;

int main(int argc, char* argv[]) {
    MPIEnvironment mpiEnvironment(argc, argv, {});

    const char* nameIn = argv[1];
    const auto threshold = std::stoi(argv[2]);
    const auto fitterVerbose = std::stoi(argv[3]);
    const auto tolerance = std::stod(argv[4]);
    const auto maxStepNR = std::stoi(argv[5]);
    const auto maxStepCG = std::stoi(argv[6]);
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
    const auto fileNameOut = MakeMPIFilePath(outName.string() + "_recTrk", ".root");
    TFile fileOut(fileNameOut.generic_string().c_str(), "recreate");

    DataFactory dataHub;
    dataHub.TreeNamePrefixFormat("Rep#_");
    auto treeIndexRange = dataHub.GetTreeIndexRange<Hit_t>(fileIn);
    auto [treeBegin, treeEnd, treeStep, _] = AllocMPIJobsJobWise(treeIndexRange, MPI_COMM_WORLD);

    CLHEP::MTwistEngine mtEng;

    std::cout << "Rank" << mpiEnvironment.GetWorldRank() << " is ready to process data of repetition " << treeBegin << " to " << treeEnd - 1 << std::endl;

    for (auto treeIndex = treeBegin; treeIndex < treeEnd; treeIndex += treeStep) {
        dataHub.TreeNamePrefixFormat("Rep#_");
        std::cout << "Now processing " << dataHub.TreeName<Hit_t>(treeIndex) << " ..." << std::endl;

        auto hitData = dataHub.CreateAndFillList<Hit_t>(fileIn, treeIndex);

        if (deltaD > 0) {
            for (auto&& hit : hitData) {
                hit->DriftDistanceVariance(deltaD);
                const auto smearD = CLHEP::RandGauss::shoot(std::addressof(mtEng), 0, deltaD);
                hit->DriftDistance(smearD + hit->DriftDistance());
            }
        }
        if (deltaZ > 0) {
            for (auto&& hit : hitData) {
                hit->HitPositionZVariance(deltaZ);
                const auto smearZ = CLHEP::RandGauss::shoot(std::addressof(mtEng), 0, deltaZ);
                hit->HitPositionZ(smearZ + hit->HitPositionZ());
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
        for (std::size_t i = 0; i < physicsTracks.size(); ++i) {
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

        dataHub.TreeNamePrefixFormat("Rep#_Omitted_");
        dataHub.CreateAndFillTree<Hit_t>(ommitedHits, treeIndex)->Write();
        dataHub.TreeNamePrefixFormat("Rep#_Perfect_");
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(perfectTracks, treeIndex)->Write();
        dataHub.TreeNamePrefixFormat("Rep#_Exact_");
        dataHub.CreateAndFillTree<CDCHelixTrack>(helixTracks, treeIndex)->Write();
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(physicsTracks, treeIndex)->Write();
        dataHub.TreeNamePrefixFormat("Rep#_Error_");
        dataHub.CreateAndFillTree<CDCPhysicsTrack>(errors, treeIndex)->Write();
    }

    fileOut.Close();
    fileIn.Close();

    return EXIT_SUCCESS;
}
