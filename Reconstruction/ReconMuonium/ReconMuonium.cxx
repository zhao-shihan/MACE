#include <numbers>

#include "TNtuple.h"

#include "CLHEP/Units/PhysicalConstants.h"

#include "DataModel/DataHub.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"
#include "DataModel/Hit/VertexDetectorHit.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Vertex/MuoniumVertex.hxx"
#include "Geometry/Description/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Description/DescendantsOfWorld/SecondBendField.hxx"
#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hxx"
#include "Geometry/Description/DescendantsOfWorld/ThirdTransportField.hxx"
#include "LiteralUnits.hxx"
#include "MPITools/MPIFileTools.hxx"
#include "MPITools/MPIJobsAssigner.hxx"

namespace sn = std::numbers;
using namespace CLHEP;
using namespace MACE;
using namespace MACE::DataModel;
using namespace MACE::Geometry::Description;

int main(int, char* argv[]) {
    MPI::Init();

    std::filesystem::path pathIn = argv[1];
    const bool coincidenceWithCal = std::stoi(argv[2]);
    const auto calTimeWindow = std::stod(argv[3]);

    // linac
    const auto linacLength = AcceleratorField::Instance().GetDownStreamLength();
    const auto accE = 7_kV / (linacLength - 13.05_mm);
    // flight
    const auto flightLength =
        SpectrometerField::Instance().GetLength() / 2 - linacLength +
        FirstTransportField::Instance().GetLength() +
        FirstBendField::Instance().GetBendRadius() * sn::pi / 2 +
        SecondTransportField::Instance().GetLength() +
        SecondBendField::Instance().GetBendRadius() * sn::pi / 2 +
        ThirdTransportField::Instance().GetLength() +
        CalorimeterField::Instance().GetLength() / 2;
    // muonium survival length (5 tau_mu @ 300K)
    const auto maxSurvivalLength = c_light * std::sqrt(3 * k_Boltzmann * 300_K / electron_mass_c2) * 5 * 2197.03_ns;
    // Time of flight range
    auto CaculateFlightTime = [&accE, &linacLength, &flightLength](double zVertex) {
        const auto velocity = c_light * std::sqrt((2 * eplus * accE / electron_mass_c2) * (linacLength - zVertex));
        return 1 / c_light * std::sqrt(2 * linacLength * electron_mass_c2 / (eplus * accE)) + flightLength / velocity;
    };
    const auto tofMax = CaculateFlightTime(maxSurvivalLength);
    const auto tofMin = CaculateFlightTime(0);
    std::cout
        << "   Linac length: " << linacLength / 1_cm << " cm\n"
        << "  Linac E field: " << accE / 1_kV_cm << " kV/cm\n"
        << "e+/- max flight: " << (linacLength + flightLength) / 1_cm << " cm\n"
        << "e+/- min flight: " << (linacLength + flightLength - maxSurvivalLength) / 1_cm << " cm\n"
        << "   e+/- max TOF: " << tofMax / 1_s << " s\n"
        << "   e+/- min TOF: " << tofMin / 1_s << " s" << std::endl;

    // original file
    TFile hitFileIn(pathIn.c_str(), "read");

    pathIn.replace_extension("");
    // reconstructed track file
    TFile trackFileIn((pathIn.string() + "_recTrk.root").c_str(), "read");

    std::filesystem::path pathOut(argv[0]);
    pathOut.replace_extension("");
    MPIFileTools mpiFileOut(pathOut.string() + "_recM", ".root");
    // output file of this rank
    TFile fileOut(mpiFileOut.GetFilePath().c_str(), "recreate");

    DataHub dataHub;

    dataHub.SetPrefixFormatOfTreeName("Rep#_");
    unsigned long allRepBegin;
    unsigned long allRepEnd;
    if (MPI::COMM_WORLD.Get_rank() == 0) {
        std::tie(allRepBegin, allRepEnd) = dataHub.GetTreeIndexRange<VertexDetectorHit>(hitFileIn);
    }
    MPI::COMM_WORLD.Bcast(std::addressof(allRepBegin), 1, MPI::UNSIGNED_LONG, 0);
    MPI::COMM_WORLD.Bcast(std::addressof(allRepEnd), 1, MPI::UNSIGNED_LONG, 0);
    const auto [repBegin, repEnd] = MPIJobsAssigner(allRepBegin, allRepEnd).GetJobsIndexRange();

    // result tree
    dataHub.SetPrefixFormatOfTreeName(TString("Rep") + allRepBegin + "To" + (allRepEnd - 1) + '_');
    auto vertexTree = dataHub.CreateTree<MuoniumVertex>();

    dataHub.SetPrefixFormatOfTreeName("Rep#_");

    for (auto rep = repBegin; rep < repEnd; ++rep) {

        auto SortByVertexTime = [](const auto& track1, const auto& track2) {
            return track1->GetVertexTime() < track2->GetVertexTime();
        };
        // Get CDC track
        auto trackData = dataHub.CreateAndFillList<HelixTrack>(trackFileIn, rep);
        std::ranges::sort(trackData, SortByVertexTime);

        auto SortByHitTime = [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        };
        // Get MCP data
        auto mcpData = dataHub.CreateAndFillList<VertexDetectorHit>(hitFileIn, rep);
        std::ranges::sort(mcpData, SortByHitTime);
        // Get calorimeter data
        std::vector<std::shared_ptr<CalorimeterHit>> calData;
        if (coincidenceWithCal) {
            calData = dataHub.CreateAndFillList<CalorimeterHit>(hitFileIn, rep);
            std::ranges::sort(calData, SortByHitTime);
        }

        // result list
        std::vector<std::shared_ptr<MuoniumVertex>> vertexData;

        // coincidence with calorimeter
        std::vector<std::shared_ptr<VertexDetectorHit>> coinedMCPData;
        if (coincidenceWithCal) {
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
                auto coinCount = coinCalHitEnd - coinCalHitBegin;
                // TODO: discriminate gamma energy.
                // select the MCP hit if coincident
                if (coinCount >= /* 2 */ 1) {  // enable 2 gamma after new cal geom :)
                    coinedMCPData.emplace_back(mcpHit);
                }
                // update for next loop
                coinCalHitBegin = coinCalHitEnd;
            }
        } else {
            coinedMCPData = std::move(mcpData);
        }

        auto coinCDCHitBegin = trackData.cbegin();
        auto coinCDCHitEnd = coinCDCHitBegin;
        for (auto&& mcpHit : mcpData) {
            // coincidence time window for this MCP hit
            const auto timeBegin = mcpHit->GetHitTime() - tofMax;
            const auto timeEnd = mcpHit->GetHitTime() - tofMin;
            // find time coincident
            std::vector<std::shared_ptr<HelixTrack>> timeCoinTrack;
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
            for (auto&& track : timeCoinTrack) {
            }
        }
    }

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
