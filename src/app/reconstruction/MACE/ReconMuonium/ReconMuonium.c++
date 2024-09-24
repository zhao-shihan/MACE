#include "MACE/DataModel/CDCTrackOperation.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/DataModel/SimHit/ECALSimHit.h++"
#include "MACE/DataModel/SimHit/MCPSimHit.h++"
#include "MACE/DataModel/Track/CDCHelixTrack.h++"
#include "MACE/DataModel/Track/CDCPhysicsTrack.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/ReconMuonium/MuoniumSimVertex.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/MPIX/AllocMPIJobs.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/VectorArithmeticOperator.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "TH2F.h"

#include <filesystem>
#include <string>

using namespace MACE;
using namespace MACE::Core::DataModel;
using namespace MACE::Core::DataModel::CDCTrackOperation;
using namespace MACE::Core::Geometry::Description;
using namespace MACE::ReconMuonium;
using namespace Mustard::LiteralUnit;
using namespace Mustard::MPIX;
using namespace Mustard::PhysicalConstant;
using namespace Mustard::VectorArithmeticOperator;

using MACE::Core::DataFactory;
using Mustard::Env::MPIEnv;

using ECALHit_t = SimHit::ECALSimHit;
using Helix_t = Track::CDCHelixTrack;
using MCPHit_t = SimHit::MCPSimHit;
using MVertex_t = MuoniumSimVertex;
using Track_t = Track::CDCPhysicsTrack;

int main(int argc, char* argv[]) {
    MPIEnv mpiEnv(argc, argv, {});

    std::filesystem::path pathIn = argv[1];
    const auto calTimeWindow = std::stod(argv[2]);
    const auto sigmaTCA = std::stod(argv[3]);
    const auto sigmaCPA = std::stod(argv[4]);
    const auto sigmaZCDC = std::stod(argv[5]);

    // accelerator
    const auto acceleratorLength = AcceleratorField::Instance().AccelerateFieldLength();
    const auto accE = 7_kV / (acceleratorLength - 13.05_mm);
    // flight
    const auto& transportLine = Solenoid::Instance();
    const auto flightLength =
        MMSField::Instance().Length() / 2 - acceleratorLength +
        transportLine.S1Length() +
        transportLine.T1Radius() * halfpi +
        transportLine.S2Length() +
        transportLine.T2Radius() * halfpi +
        transportLine.S3Length() +
        ECALField::Instance().Length() / 2;
    // muonium survival length (5 tau_mu @ 300K)
    const auto maxSurvivalLength = c_light * std::sqrt(3 * k_Boltzmann * 300_K / muonium_mass_c2) * 5 * 2197.03_ns;
    auto CalculateFlightTime = [&accE, &acceleratorLength, &flightLength](double zVertex) {
        const auto velocity = c_light * std::sqrt((2 * eplus * accE / electron_mass_c2) * (acceleratorLength - zVertex));
        const auto accTime = velocity / (eplus * accE * c_squared / electron_mass_c2);
        return accTime + flightLength / velocity + 1.0906_ns; // TODO: figure out the magic 1.0906_ns
    };
    // Time of flight range
    const auto tofMax = CalculateFlightTime(maxSurvivalLength + 3 * sigmaZCDC);
    const auto tofMin = CalculateFlightTime(-3 * sigmaZCDC);
    std::cout
        << "   Accelerator length: " << acceleratorLength / 1_cm << " cm\n"
        << "  M max survive: " << maxSurvivalLength / 1_cm << " cm\n"
        << "  Accelerator E field: " << accE / 1_kV_cm << " kV/cm\n"
        << "e+/- max flight: " << (acceleratorLength + flightLength) / 1_cm << " cm\n"
        << "e+/- min flight: " << (acceleratorLength + flightLength - maxSurvivalLength) / 1_cm << " cm\n"
        << "   e+/- max TOF: " << tofMax / 1_ns << " ns\n"
        << "   e+/- min TOF: " << tofMin / 1_ns << " ns" << std::endl;

    // original file
    TFile hitFileIn(pathIn.generic_string().c_str(), "read");

    pathIn.replace_extension("");
    // reconstructed track file
    TFile trackFileIn((pathIn.string() + "_recTrk.root").c_str(), "read");

    std::filesystem::path pathOut(argv[1]);
    pathOut.replace_extension("");
    const auto fileNameOut = ParallelizePath(pathOut.string() + "_recM", ".root");
    // output file of this process
    TFile fileOut(fileNameOut.generic_string().c_str(), "recreate");

    DataFactory dataHub;

    dataHub.TreeNamePrefixFormat("Rep{}_");
    auto [allRepBegin, allRepEnd] = dataHub.GetTreeIndexRange<MCPHit_t>(hitFileIn);
    auto [repBegin, repEnd, repStep, _] = AllocMPIJobsJobWise(allRepBegin, allRepEnd, MPI_COMM_WORLD);

    // result tree
    dataHub.TreeNamePrefixFormat("Rep" + std::to_string(allRepBegin) + "To" + std::to_string(allRepEnd - 1) + '_');
    auto vertexTree = dataHub.CreateTree<MVertex_t>();
    TH2F vertexHist("vertex", "(Anti-)Muonium Vertex", 500, -20, 20, 500, -50, 50);

    for (auto rep = repBegin; rep < repEnd; rep += repStep) {

        auto SortByVertexTime = [](const auto& track1, const auto& track2) {
            return track1->VertexTime() < track2->VertexTime();
        };
        // Get CDC track
        dataHub.TreeNamePrefixFormat("Rep{}_Exact_");
        auto trackData = dataHub.CreateAndFillList<Helix_t>(trackFileIn, rep);
        std::ranges::sort(trackData, SortByVertexTime);
        dataHub.TreeNamePrefixFormat("Rep{}_");

        auto SortByHitTime = [](const auto& hit1, const auto& hit2) {
            return hit1->HitTime() < hit2->HitTime();
        };
        // Get MCP data
        auto mcpData = dataHub.CreateAndFillList<MCPHit_t>(hitFileIn, rep);
        std::ranges::sort(mcpData, SortByHitTime);
        // Get ECAL data
        std::vector<std::shared_ptr<ECALHit_t>> calData;
        calData = dataHub.CreateAndFillList<ECALHit_t>(hitFileIn, rep);
        std::ranges::sort(calData, SortByHitTime);

        // result list
        std::vector<std::shared_ptr<MVertex_t>> vertexResult;

        // coincidence with ECAL
        std::vector<std::pair<std::shared_ptr<MCPHit_t>, int>> coinedMCPData;
        auto coinCalHitBegin = calData.cbegin();
        auto coinCalHitEnd = coinCalHitBegin;
        for (auto&& mcpHit : mcpData) {
            // coincidence time window for this MCP hit
            const auto timeBegin = mcpHit->HitTime() - calTimeWindow / 2;
            const auto timeEnd = timeBegin + calTimeWindow;
            // find coincident
            coinCalHitBegin = std::find_if(coinCalHitBegin, calData.cend(),
                                           [&timeBegin](const auto& hit) {
                                               return hit->HitTime() > timeBegin;
                                           });
            coinCalHitEnd = std::find_if(coinCalHitBegin, calData.cend(),
                                         [&timeEnd](const auto& hit) {
                                             return hit->HitTime() > timeEnd;
                                         });
            // coincident count
            int coinCount = 0;
            for (; coinCalHitBegin != coinCalHitEnd; ++coinCalHitBegin) {
                const auto& energy = (*coinCalHitBegin)->Energy();
                if (480_keV < energy and energy < 540_keV) { ++coinCount; }
            }
            // select the MCP hit if coincident
            coinedMCPData.emplace_back(mcpHit, coinCount);
        }

        auto coinCDCHitBegin = trackData.cbegin();
        auto coinCDCHitEnd = coinCDCHitBegin;
        for (auto&& [mcpHit, ecalCoinCount] : std::as_const(coinedMCPData)) {
            // result list
            std::vector<std::shared_ptr<MVertex_t>> vertexResultOfThisHit;
            // coincidence time window for this MCP hit
            const auto timeBegin = mcpHit->HitTime() - tofMax;
            const auto timeEnd = mcpHit->HitTime() - tofMin;
            // find time coincident
            std::vector<std::shared_ptr<Helix_t>> timeCoinTrack;
            coinCDCHitBegin = std::find_if(coinCDCHitBegin, trackData.cend(),
                                           [&timeBegin](const auto& track) {
                                               return track->VertexTime() > timeBegin;
                                           });
            coinCDCHitEnd = std::find_if(coinCDCHitBegin, trackData.cend(),
                                         [&timeEnd](const auto& track) {
                                             return track->VertexTime() > timeEnd;
                                         });
            timeCoinTrack.insert(timeCoinTrack.cend(), coinCDCHitBegin, coinCDCHitEnd);
            // do space coin
            for (auto&& track : std::as_const(timeCoinTrack)) {
                const auto& CPAMCP = mcpHit->HitPosition();
                const auto phiMCP = track->CalcPhi(Mustard::VectorCast<Eigen::Vector2d>(CPAMCP));
                const auto CPACDC = track->CalcPoint(phiMCP);
                const auto& TCACDC = track->VertexTime();
                const auto TCAMCP = mcpHit->HitTime() - CalculateFlightTime(CPACDC.z());

                if (-3 * sigmaZCDC < CPACDC.z() and CPACDC.z() < maxSurvivalLength + 3 * sigmaZCDC) {
                    Track_t physTrack(*track, phiMCP);

                    auto& possibleVertex = vertexResultOfThisHit.emplace_back(std::make_shared<MVertex_t>());
                    possibleVertex->SetTCACDC(TCACDC);
                    possibleVertex->SetTCAMCP(TCAMCP);
                    possibleVertex->SetDeltaTCA(TCACDC - TCAMCP);
                    possibleVertex->SetCPACDC(CPACDC);
                    possibleVertex->SetCPAMCP(CPAMCP);
                    possibleVertex->SetDCA(track->Radius() - (track->GetCenter() - CPAMCP).norm());
                    possibleVertex->VertexEnergy(physTrack.VertexEnergy());
                    possibleVertex->VertexMomentum(physTrack.VertexMomentum());
                    const auto particles = std::to_string(ecalCoinCount) + "y/" + physTrack.Particle();
                    possibleVertex->SetParticles(particles);

                    possibleVertex->TrueVertexTime(mcpHit->VertexTime());
                    possibleVertex->TrueVertexPosition(mcpHit->VertexPosition());
                    const auto trueParticles = mcpHit->Particle() + "/" + physTrack.Particle();
                    possibleVertex->TrueParticles(trueParticles);
                }
            }
            if (not vertexResultOfThisHit.empty()) {
                const auto theVertex = *std::ranges::min_element(
                    vertexResultOfThisHit,
                    [&sigmaTCA, &sigmaCPA](const auto& vertex1, const auto& vertex2) {
                        const auto chiSq1 = Eigen::Vector2d(vertex1->GetDeltaTCA() / sigmaTCA, vertex1->GetDCA() / sigmaCPA).squaredNorm();
                        const auto chiSq2 = Eigen::Vector2d(vertex2->GetDeltaTCA() / sigmaTCA, vertex2->GetDCA() / sigmaCPA).squaredNorm();
                        return chiSq1 < chiSq2;
                    });
                vertexResult.emplace_back(theVertex);
                vertexHist.Fill(theVertex->GetDeltaTCA(), theVertex->GetDCA());
            }
        }
        dataHub.FillTree<MVertex_t>(vertexResult, *vertexTree, true);
    }

    vertexTree->Write();
    vertexHist.Write();

    return EXIT_SUCCESS;
}
