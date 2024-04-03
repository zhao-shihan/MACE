#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/TakeFrom.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Extension/MPIX/DataType.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"
#include "MACE/Utility/RDFEventSplitPoint.h++"

#include "ROOT/RDataFrame.hxx"

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

    MPIX::Executor<unsigned> executor;
    executor.Execute(eventSplitPoint.size() - 1,
                     [&](auto i) {
                         Env::Print<'W'>("{} ", Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1])).size());
                         // Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1]));
                         // *cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1]).Count();
                     });

    return EXIT_SUCCESS;
}
