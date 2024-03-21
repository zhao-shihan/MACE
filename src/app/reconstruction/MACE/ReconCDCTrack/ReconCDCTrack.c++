#include "MACE/Data/CDCTrack.h++"
#include "MACE/Data/Hit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/TakeFrom.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/DataType.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"
#include "MACE/Utility/FindRDFEventSplitPoint.h++"

#include "ROOT/RDataFrame.hxx"

#include "mpi.h"

#include "fmt/format.h"

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

    ROOT::RDataFrame cdcSimHit{"G4Run0/CDCSimHit", argv[1]};
    const auto eventSplitPoint{FindRDFEventSplitPoint(cdcSimHit)};

    MPIX::Executor<unsigned> executor;
    executor.Execute(eventSplitPoint.size() - 1,
                     [&](auto i) {
                         fmt::print("{} ", Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1])).size());
                         // Data::Take<Data::CDCSimHit>::From(cdcSimHit.Range(eventSplitPoint[i], eventSplitPoint[i + 1]));
                     });

    return EXIT_SUCCESS;
}
