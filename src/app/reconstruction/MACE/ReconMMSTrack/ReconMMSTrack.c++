#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/TakeFrom.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Extension/MPIX/DataType.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"
#include "MACE/Utility/RDFEventSplitPoint.h++"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"

#include "mpi.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::MPIEnv env{argc, argv, {}};

    std::vector<std::string> files;
    for (auto i{1}; i < argc; ++i) { files.emplace_back(argv[i]); }

    ROOT::RDataFrame cdcSimHit{"G4Run0/CDCSimHit", files};
    const auto eventSplitPoint{RDFEventSplitPoint(cdcSimHit)};

    MMSTracking::TruthFinder finder;

    TFile file{MPIX::ParallelizePath("output.root").generic_string().c_str(), "RECREATE"};
    Data::Output<Data::MMSTrack> reconTrack{"G4Run0/MMSTrack"};

    MPIX::Executor<unsigned> executor;
    executor.Execute(eventSplitPoint.size() - 1,
                     [&](auto i) {
                         for (auto&& [trackID, good] : finder(Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1]))).good) {
                             reconTrack.Fill(*good.seed);
                         }
                     });

    reconTrack.Write();

    return EXIT_SUCCESS;
}
