#include "MACE/Data/SimHit.h++"
#include "MACE/Detector/Description/ECal.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Processor.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Env/Print.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/VectorArithmeticOperator.h++"

#include "CLHEP/Vector/ThreeVector.h"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TTree.h"

#include "muc/algorithm"

#include <unordered_map>

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Mustard::Env::MPIEnv env{argc, argv, {}};

    // std::vector<std::string> files;
    // for (auto i{1}; i < argc; ++i) { files.emplace_back(argv[i]); }
    std::string fileName{argv[1]};
    std::string filePath{"../../../simulation/MACE/PhaseI/SimMACEPhaseI/"};

    const auto& eCal{Detector::Description::ECal::Instance()};
    const auto& faceList{eCal.Mesh().fFaceList};
    const auto& clusterMap{eCal.Mesh().fClusterMap};

    std::map<int, CLHEP::Hep3Vector> centroidMap;

    for (int i{}; auto&& [centroid, _1, _2] : std::as_const(faceList)) {
        centroidMap[i] = centroid;
        i++;
    }

    TFile outputFile{Mustard::MPIX::ParallelizePath("recon_" + fileName).generic_string().c_str(), "RECREATE"};
    using ECALEnergy = Mustard::Data::TupleModel<Mustard::Data::Value<float, "Edep", "Energy deposition">>;
    Mustard::Data::Output<ECALEnergy> reconEnergy{"G4Run0/ReconECAL"};

    Mustard::Data::Processor processor;
    processor.Process<Data::ECalSimHit>(
        ROOT::RDataFrame{"G4Run0/ECalSimHit", filePath + fileName}, "EvtID",
        [&](bool byPass, auto&& event) {
            if (byPass) { return; }
            muc::timsort(event,
                         [](auto&& hit1, auto&& hit2) {
                             return Get<"Edep">(*hit1) > Get<"Edep">(*hit2);
                         });

            std::unordered_map<short, std::shared_ptr<Mustard::Data::Tuple<Data::ECalSimHit>>> hitDict;

            std::vector<short> potentialSeed;

            for (int i{}; auto&& hit : event) {
                if (i < 3) {
                    potentialSeed.emplace_back(Get<"UnitID">(*hit));
                }
                hitDict.try_emplace(Get<"UnitID">(*hit), hit);
                i++;
            }

            std::unordered_set<short> firstCluster;
            auto seedModule = potentialSeed.begin();
            auto adjacentModules = clusterMap.at(*seedModule);

            firstCluster.insert(*seedModule);
            for (auto&& m : adjacentModules) {
                firstCluster.insert(m);
                firstCluster.insert(clusterMap.at(m).begin(), clusterMap.at(m).end());
            }

            float clusterEnergy{};

            std::unordered_set<short> secondCluster;
            auto candSeedModule = std::next(potentialSeed.begin(), 1);

            if (candSeedModule != potentialSeed.end()) {
                auto adjacentCand = clusterMap.at(*candSeedModule);
                secondCluster.insert(*candSeedModule);

                for (auto&& m : adjacentCand) {
                    secondCluster.insert(m);
                    secondCluster.insert(clusterMap.at(m).begin(), clusterMap.at(m).end());
                }

                if (centroidMap.at(*seedModule).angle(centroidMap.at(*candSeedModule)) > 0.8 * CLHEP::pi and
                    Get<"Edep">(*hitDict.at(*candSeedModule)) > 20) {

                    for (auto&& m : firstCluster) {
                        if (hitDict.find(m) != hitDict.end()) {
                            clusterEnergy += Get<"Edep">(*hitDict.at(m));
                        }
                    }
                    for (auto&& m : secondCluster) {
                        if (hitDict.find(m) != hitDict.end()) {
                            clusterEnergy += Get<"Edep">(*hitDict.at(m));
                        }
                    }

                    Mustard::Data::Tuple<ECALEnergy> energyTuple;
                    Get<"Edep">(energyTuple) = clusterEnergy;
                    reconEnergy.Fill(energyTuple);
                }
            }
        });

    reconEnergy.Write();

    return EXIT_SUCCESS;
}
