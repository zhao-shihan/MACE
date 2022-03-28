#include "Core/DataModel/DataHub.hxx"
#include "Core/DataModel/SimHit/CalorimeterSimHit.hxx"
#include "Core/DataModel/SimHit/VertexDetectorSimHit.hxx"
#include "Core/DataModel/SimVertex/MuoniumSimVertex.hxx"
#include "Core/DataModel/Track/HelixTrack.hxx"
#include "Core/DataModel/Track/PhysicsTrack.hxx"
#include "Core/Geometry/Description/AcceleratorField.hxx"
#include "Core/Geometry/Description/CalorimeterField.hxx"
#include "Core/Geometry/Description/FirstBendField.hxx"
#include "Core/Geometry/Description/FirstTransportField.hxx"
#include "Core/Geometry/Description/SecondBendField.hxx"
#include "Core/Geometry/Description/SecondTransportField.hxx"
#include "Core/Geometry/Description/SpectrometerField.hxx"
#include "Core/Geometry/Description/ThirdTransportField.hxx"
#include "Utility/LiteralUnit.hxx"
#include "Utility/MPITools/MPIFileTools.hxx"
#include "Utility/MPITools/MPIJobsAssigner.hxx"
#include "Utility/PhysicalConstant.hxx"

#include "TH2F.h"

using namespace MACE::Utility::PhysicalConstant;
using namespace MACE::Utility::LiteralUnit;
using namespace MACE::Utility::MPITools;
using namespace MACE::Geometry::Description;
using namespace MACE::Core::DataModel;

using MACE::Core::DataModel::DataHub;

using Helix_t = Track::HelixTrack;
using Track_t = Track::PhysicsTrack;
using EMCalHit_t = SimHit::CalorimeterSimHit;
using MCPHit_t = SimHit::VertexDetectorSimHit;
using MVertex_t = SimVertex::MuoniumSimVertex;

int main(int, char* argv[]) {
    MPI::Init();

    std::filesystem::path pathIn = argv[1];
    const auto calTimeWindow = std::stod(argv[2]);
    const auto sigmaTCA = std::stod(argv[3]);
    const auto sigmaCPA = std::stod(argv[4]);
    const auto sigmaZCDC = std::stod(argv[5]);

    // linac
    const auto linacLength = AcceleratorField::Instance().GetDownStreamLength();
    const auto accE = 7_kV / (linacLength - 13.05_mm);
    // flight
    const auto flightLength =
        SpectrometerField::Instance().GetLength() / 2 - linacLength +
        FirstTransportField::Instance().GetLength() +
        FirstBendField::Instance().GetBendRadius() * halfpi +
        SecondTransportField::Instance().GetLength() +
        SecondBendField::Instance().GetBendRadius() * halfpi +
        ThirdTransportField::Instance().GetLength() +
        CalorimeterField::Instance().GetLength() / 2;
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
    TFile hitFileIn(pathIn.c_str(), "read");

    pathIn.replace_extension("");
    // reconstructed track file
    TFile trackFileIn((pathIn.string() + "_recTrk.root").c_str(), "read");

    std::filesystem::path pathOut(argv[1]);
    pathOut.replace_extension("");
    MPIFileTools mpiFileOut(pathOut.string() + "_recM", ".root");
    // output file of this rank
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataHub dataHub;

    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    unsigned long allRepBegin;
    unsigned long allRepEnd;
    if (MPI::COMM_WORLD.Get_rank() == 0) {
        std::tie(allRepBegin, allRepEnd) = dataHub.GetTreeIndexRange<MCPHit_t>(hitFileIn);
    }
    MPI::COMM_WORLD.Bcast(std::addressof(allRepBegin), 1, MPI::UNSIGNED_LONG, 0);
    MPI::COMM_WORLD.Bcast(std::addressof(allRepEnd), 1, MPI::UNSIGNED_LONG, 0);
    const auto [repBegin, repEnd] = MPIJobsAssigner(allRepBegin, allRepEnd).GetJobsIndexRange();

    // result tree
    dataHub.SetPrefixFormatOfTreeName(TString("Rep") + allRepBegin + "To" + (allRepEnd - 1) + '_');
    auto vertexTree = dataHub.CreateTree<MVertex_t>();
    TH2F vertexHist("vertex", "(Anti-)Muonium Vertex", 500, -20, 20, 500, -50, 50);

    for (auto rep = repBegin; rep < repEnd; ++rep) {

        auto SortByVertexTime = [](const auto& track1, const auto& track2) {
            return track1->GetVertexTime() < track2->GetVertexTime();
        };
        // Get CDC track
        dataHub.SetPrefixFormatOfTreeName("Rep#_Exact_");
        auto trackData = dataHub.CreateAndFillList<Helix_t>(trackFileIn, rep);
        std::ranges::sort(trackData, SortByVertexTime);
        dataHub.SetPrefixFormatOfTreeName("Rep#_");

        auto SortByHitTime = [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        };
        // Get MCP data
        auto mcpData = dataHub.CreateAndFillList<MCPHit_t>(hitFileIn, rep);
        std::ranges::sort(mcpData, SortByHitTime);
        // Get calorimeter data
        std::vector<std::shared_ptr<EMCalHit_t>> calData;
        calData = dataHub.CreateAndFillList<EMCalHit_t>(hitFileIn, rep);
        std::ranges::sort(calData, SortByHitTime);

        // result list
        std::vector<std::shared_ptr<MVertex_t>> vertexResult;

        // coincidence with calorimeter
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
                const auto TCAMCP = mcpHit->GetHitTime() - CalculateFlightTime(CPACDC.fZ);

                if (-3 * sigmaZCDC < CPACDC.fZ and CPACDC.fZ < maxSurvivalLength + 3 * sigmaZCDC) {
                    Track_t physTrack(*track, phiMCP);

                    auto& possibleVertex = vertexResultOfThisHit.emplace_back(std::make_shared<MVertex_t>());
                    possibleVertex->SetTCACDC(TCACDC);
                    possibleVertex->SetTCAMCP(TCAMCP);
                    possibleVertex->SetDeltaTCA(TCACDC - TCAMCP);
                    possibleVertex->SetCPACDC(CPACDC);
                    possibleVertex->SetCPAMCP(CPAMCP);
                    possibleVertex->SetDCA(track->GetRadius() - (track->GetCenter() - CPAMCP).Mag());
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
                        const auto chiSq1 = TEveVector2D(vertex1->GetDeltaTCA() / sigmaTCA, vertex1->GetDCA() / sigmaCPA).Mag2();
                        const auto chiSq2 = TEveVector2D(vertex2->GetDeltaTCA() / sigmaTCA, vertex2->GetDCA() / sigmaCPA).Mag2();
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

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
