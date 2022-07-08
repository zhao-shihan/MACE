#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/CDCTrackOperation.hxx"
#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"
#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"
#include "MACE/Core/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Reconstruction/ReconMuonium/MuoniumSimVertex.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"
#include "MACE/Utility/MPIUtil/MainMPI.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "TH2F.h"

using namespace MACE::Core::DataModel;
using namespace MACE::Core::DataModel::CDCTrackOperation;
using namespace MACE::Core::Geometry::Description;
using namespace MACE::Reconstruction::ReconMuonium;
using namespace MACE::Utility;
using namespace MACE::Utility::LiteralUnit;
using namespace MACE::Utility::MPIUtil;
using namespace MACE::Utility::PhysicalConstant;

using MACE::Core::DataFactory;

using EMCalHit_t = SimHit::EMCalSimHit;
using Helix_t = Track::CDCHelixTrack;
using MCPHit_t = SimHit::MCPSimHit;
using MVertex_t = MuoniumSimVertex;
using Track_t = Track::CDCPhysicsTrack;

int main_MPI(int, char* argv[]) {
    std::filesystem::path pathIn = argv[1];
    const auto calTimeWindow = std::stod(argv[2]);
    const auto sigmaTCA = std::stod(argv[3]);
    const auto sigmaCPA = std::stod(argv[4]);
    const auto sigmaZCDC = std::stod(argv[5]);

    // linac
    const auto linacLength = LinacField::Instance().GetDownStreamLength();
    const auto accE = 7_kV / (linacLength - 13.05_mm);
    // flight
    const auto& transportLine = TransportLine::Instance();
    const auto flightLength =
        SpectrometerField::Instance().GetLength() / 2 - linacLength +
        transportLine.GetFirstStraightLength() +
        transportLine.GetFirstBendRadius() * halfpi +
        transportLine.GetSecondStraightLength() +
        transportLine.GetSecondBendRadius() * halfpi +
        transportLine.GetThirdStraightLength() +
        EMCalField::Instance().GetLength() / 2;
    // muonium survival length (5 tau_mu @ 300K)
    const auto maxSurvivalLength = c_light * std::sqrt(3 * k_Boltzmann * 300_K / muonium_mass_c2) * 5 * 2197.03_ns;
    auto CalculateFlightTime = [&accE, &linacLength, &flightLength](double zVertex) {
        const auto velocity = c_light * std::sqrt((2 * eplus * accE / electron_mass_c2) * (linacLength - zVertex));
        const auto accTime = velocity / (eplus * accE * c_squared / electron_mass_c2);
        return accTime + flightLength / velocity + 1.0906_ns; // TODO: figure out the magic 1.0906_ns
    };
    // Time of flight range
    const auto tofMax = CalculateFlightTime(maxSurvivalLength + 3 * sigmaZCDC);
    const auto tofMin = CalculateFlightTime(-3 * sigmaZCDC);
    std::cout
        << "   Linac length: " << linacLength / 1_cm << " cm\n"
        << "  M max survive: " << maxSurvivalLength / 1_cm << " cm\n"
        << "  Linac E field: " << accE / 1_kV_cm << " kV/cm\n"
        << "e+/- max flight: " << (linacLength + flightLength) / 1_cm << " cm\n"
        << "e+/- min flight: " << (linacLength + flightLength - maxSurvivalLength) / 1_cm << " cm\n"
        << "   e+/- max TOF: " << tofMax / 1_ns << " ns\n"
        << "   e+/- min TOF: " << tofMin / 1_ns << " ns" << std::endl;

    // original file
    TFile hitFileIn(pathIn.generic_string().c_str(), "read");

    pathIn.replace_extension("");
    // reconstructed track file
    TFile trackFileIn((pathIn.string() + "_recTrk.root").c_str(), "read");

    std::filesystem::path pathOut(argv[1]);
    pathOut.replace_extension("");
    const auto fileNameOut = MakeMPIFilePath(pathOut.string() + "_recM", ".root");
    // output file of this rank
    TFile fileOut(fileNameOut.generic_string().c_str(), "recreate");

    DataFactory dataHub;

    dataHub.SetTreeNamePrefixFormat("Rep#_");
    auto [allRepBegin, allRepEnd] = dataHub.GetTreeIndexRange<MCPHit_t>(hitFileIn);
    auto [repBegin, repEnd, repStep, _] = AllocMPIJobsJobWise(allRepBegin, allRepEnd, MPI_COMM_WORLD);

    // result tree
    dataHub.SetTreeNamePrefixFormat(TString("Rep") + allRepBegin + "To" + (allRepEnd - 1) + '_');
    auto vertexTree = dataHub.CreateTree<MVertex_t>();
    TH2F vertexHist("vertex", "(Anti-)Muonium Vertex", 500, -20, 20, 500, -50, 50);

    for (auto rep = repBegin; rep < repEnd; rep += repStep) {

        auto SortByVertexTime = [](const auto& track1, const auto& track2) {
            return track1->GetVertexTime() < track2->GetVertexTime();
        };
        // Get CDC track
        dataHub.SetTreeNamePrefixFormat("Rep#_Exact_");
        auto trackData = dataHub.CreateAndFillList<Helix_t>(trackFileIn, rep);
        std::ranges::sort(trackData, SortByVertexTime);
        dataHub.SetTreeNamePrefixFormat("Rep#_");

        auto SortByHitTime = [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        };
        // Get MCP data
        auto mcpData = dataHub.CreateAndFillList<MCPHit_t>(hitFileIn, rep);
        std::ranges::sort(mcpData, SortByHitTime);
        // Get EMCal data
        std::vector<std::shared_ptr<EMCalHit_t>> calData;
        calData = dataHub.CreateAndFillList<EMCalHit_t>(hitFileIn, rep);
        std::ranges::sort(calData, SortByHitTime);

        // result list
        std::vector<std::shared_ptr<MVertex_t>> vertexResult;

        // coincidence with EMCal
        std::vector<std::pair<std::shared_ptr<MCPHit_t>, int>> coinedMCPData;
        auto coinCalHitBegin = calData.cbegin();
        auto coinCalHitEnd = coinCalHitBegin;
        for (auto&& mcpHit : mcpData) {
            // coincidence time window for this MCP hit
            const auto timeBegin = mcpHit->GetHitTime() - calTimeWindow / 2;
            const auto timeEnd = timeBegin + calTimeWindow;
            // find coincident
            coinCalHitBegin = std::find_if(coinCalHitBegin, calData.cend(),
                                           [&timeBegin](const auto& hit) {
                                               return hit->GetHitTime() > timeBegin;
                                           });
            coinCalHitEnd = std::find_if(coinCalHitBegin, calData.cend(),
                                         [&timeEnd](const auto& hit) {
                                             return hit->GetHitTime() > timeEnd;
                                         });
            // coincident count
            int coinCount = 0;
            for (; coinCalHitBegin != coinCalHitEnd; ++coinCalHitBegin) {
                const auto& energy = (*coinCalHitBegin)->GetEnergy();
                if (480_keV < energy and energy < 540_keV) { ++coinCount; }
            }
            // select the MCP hit if coincident
            coinedMCPData.emplace_back(mcpHit, coinCount);
        }

        auto coinCDCHitBegin = trackData.cbegin();
        auto coinCDCHitEnd = coinCDCHitBegin;
        for (auto&& [mcpHit, emCalCoinCount] : std::as_const(coinedMCPData)) {
            // result list
            std::vector<std::shared_ptr<MVertex_t>> vertexResultOfThisHit;
            // coincidence time window for this MCP hit
            const auto timeBegin = mcpHit->GetHitTime() - tofMax;
            const auto timeEnd = mcpHit->GetHitTime() - tofMin;
            // find time coincident
            std::vector<std::shared_ptr<Helix_t>> timeCoinTrack;
            coinCDCHitBegin = std::find_if(coinCDCHitBegin, trackData.cend(),
                                           [&timeBegin](const auto& track) {
                                               return track->GetVertexTime() > timeBegin;
                                           });
            coinCDCHitEnd = std::find_if(coinCDCHitBegin, trackData.cend(),
                                         [&timeEnd](const auto& track) {
                                             return track->GetVertexTime() > timeEnd;
                                         });
            timeCoinTrack.insert(timeCoinTrack.cend(), coinCDCHitBegin, coinCDCHitEnd);
            // do space coin
            for (auto&& track : std::as_const(timeCoinTrack)) {
                const auto& CPAMCP = mcpHit->GetHitPosition();
                const auto phiMCP = track->CalcPhi(CPAMCP);
                const auto CPACDC = track->CalcPoint(phiMCP);
                const auto& TCACDC = track->GetVertexTime();
                const auto TCAMCP = mcpHit->GetHitTime() - CalculateFlightTime(CPACDC.z());

                if (-3 * sigmaZCDC < CPACDC.z() and CPACDC.z() < maxSurvivalLength + 3 * sigmaZCDC) {
                    Track_t physTrack(*track, phiMCP);

                    auto& possibleVertex = vertexResultOfThisHit.emplace_back(std::make_shared<MVertex_t>());
                    possibleVertex->SetTCACDC(TCACDC);
                    possibleVertex->SetTCAMCP(TCAMCP);
                    possibleVertex->SetDeltaTCA(TCACDC - TCAMCP);
                    possibleVertex->SetCPACDC(CPACDC);
                    possibleVertex->SetCPAMCP(CPAMCP);
                    possibleVertex->SetDCA(track->GetRadius() - (track->GetCenter() - CPAMCP).norm());
                    possibleVertex->SetVertexEnergy(physTrack.GetVertexEnergy());
                    possibleVertex->SetVertexMomentum(physTrack.GetVertexMomentum());
                    const auto particles = emCalCoinCount + ("y/" + physTrack.GetParticle());
                    possibleVertex->SetParticles(particles);

                    possibleVertex->SetTrueVertexTime(mcpHit->GetVertexTime());
                    possibleVertex->SetTrueVertexPosition(mcpHit->GetVertexPosition());
                    const auto trueParticles = mcpHit->GetParticle() + '/' + physTrack.GetParticle();
                    possibleVertex->SetTrueParticles(trueParticles);
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
