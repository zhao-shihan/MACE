#include "TNtuple.h"

#include "DataModel/DataHub.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"
#include "DataModel/Hit/VertexDetectorHit.hxx"
#include "MPITools/MPIFileTools.hxx"
#include "MPITools/MPIJobsAssigner.hxx"

using namespace MACE::MPITools;
using namespace MACE::DataModel;

int main(int, char* argv[]) {
    MPI::Init();

    std::filesystem::path pathIn = argv[1];
    const bool coincidenceWithCal = std::stoi(argv[2]);
    const auto calTimeWindow = std::stod(argv[3]);

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
    // TNtuple result()

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

    for (auto rep = repBegin; rep < repEnd; ++rep) {
        auto SortByHitTime = [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        };
        auto SortByVertexTime = [](const auto& track1, const auto& track2) {
            return track1->GetVertexTime() < track2->GetVertexTime();
        };
        auto trackData = dataHub.CreateAndFillList<HelixTrack>(trackFileIn, rep);
        std::ranges::sort(trackData, SortByVertexTime);
        auto mcpData = dataHub.CreateAndFillList<VertexDetectorHit>(hitFileIn, rep);
        std::ranges::sort(mcpData, SortByHitTime);
        std::vector<std::shared_ptr<CalorimeterHit>> calData;
        if (coincidenceWithCal) {
            calData = dataHub.CreateAndFillList<CalorimeterHit>(hitFileIn, rep);
            std::ranges::sort(calData, SortByHitTime);
        }

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
                    }
                );
                coinCalHitEnd = std::find_if(coinCalHitBegin, calData.cend(),
                    [&timeEnd](const auto& hit) {
                        return hit->GetHitTime() > timeEnd;
                    }
                );
                // coincident count
                auto coinCount = coinCalHitEnd - coinCalHitBegin;
                // TODO: discriminate gamma energy.
                // select the MCP hit if coincident
                if (coinCount >= /* 2 */1) { // enable 2 gamma after new cal geom :)
                    coinedMCPData.emplace_back(mcpHit);
                }
                // update for next loop
                coinCalHitBegin = coinCalHitEnd;
            }
        } else {
            coinedMCPData = std::move(mcpData);
        }


    }

    mpiFileOut.MergeRootFiles(true);

    MPI::Finalize();
    return EXIT_SUCCESS;
}
