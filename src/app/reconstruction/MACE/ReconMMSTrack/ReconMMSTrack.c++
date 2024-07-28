#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Processor.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Env/Print.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

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

    TFile file{Mustard::MPIX::ParallelizePath("output.root").generic_string().c_str(), "RECREATE"};
    Mustard::Data::Output<Data::MMSTrack> reconTrack{"G4Run0/MMSTrack"};

    MMSTracking::TruthFinder finder;

    Mustard::Data::Processor processor;
    processor.Process<"EvtID", Data::CDCSimHit>(
        ROOT::RDataFrame{"G4Run0/CDCSimHit", files},
        [&](auto&& event) {
            for (auto&& [trackID, good] : finder(event).good) {
                reconTrack.Fill(*good.seed);
            }
        });

    reconTrack.Write();

    return EXIT_SUCCESS;
}
