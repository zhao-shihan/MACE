#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Reconstruction/MMSTracking/Finder/TruthFinder.h++"
#include "MACE/Reconstruction/MMSTracking/Fitter/TruthFitter.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Processor.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Env/Print.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"

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
    MMSTracking::TruthFitter fitter;

    Mustard::Data::Processor processor;
    processor.Process<Data::CDCSimHit>(
        ROOT::RDataFrame{"G4Run0/CDCSimHit", files}, "EvtID",
        [&](bool byPass, auto&& event) {
            if (byPass) { return; }
            for (auto&& [trackID, good] : finder(event).good) {
                reconTrack.Fill(*fitter(good.hitData, good.seed));
            }
        });

    reconTrack.Write();

    return EXIT_SUCCESS;
}
