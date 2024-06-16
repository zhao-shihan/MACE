#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "Mustard/Data/Output.h++"
#include "MACE/Data/SimHit.h++"
#include "Mustard/Data/TakeFrom.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Env/Print.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Extension/MPIX/Execution/Executor.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"
#include "Mustard/Utility/RDFEventSplitPoint.h++"

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
    Mustard::Env::MPIEnv env{argc, argv, {}};

    std::vector<std::string> files;
    for (auto i{1}; i < argc; ++i) { files.emplace_back(argv[i]); }

    ROOT::RDataFrame cdcSimHit{"G4Run0/CDCSimHit", files};
    const auto eventSplitPoint{Mustard::RDFEventSplitPoint(cdcSimHit)};

    MMSTracking::TruthFinder finder;

    TFile file{Mustard::MPIX::ParallelizePath("output.root").generic_string().c_str(), "RECREATE"};
    Mustard::Data::Output<Data::MMSTrack> reconTrack{"G4Run0/MMSTrack"};

    Mustard::MPIX::Executor<unsigned> executor;
    executor.Execute(eventSplitPoint.size() - 1,
                     [&](auto i) {
                         for (auto&& [trackID, good] : finder(Mustard::Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1]))).good) {
                             reconTrack.Fill(*good.seed);
                         }
                     });

    reconTrack.Write();

    return EXIT_SUCCESS;
}
