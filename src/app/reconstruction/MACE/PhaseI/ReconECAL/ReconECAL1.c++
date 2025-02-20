#include "MACE/Data/SimHit.h++"
#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/PhaseI/Detector/Description/UsePhaseIDefault.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Processor.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/VectorArithmeticOperator.h++"

#include "CLHEP/Vector/ThreeVector.h"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TRandom.h"
#include "TTree.h"

#include "muc/algorithm"

#include "fmt/format.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <unordered_map>
#include <unordered_set>

using namespace MACE;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::LiteralUnit::Time;
using namespace Mustard::MathConstant;
using namespace Mustard::PhysicalConstant;

auto main(int argc, char* argv[]) -> int {
    Mustard::Env::MPIEnv env{argc, argv, {}};
    Mustard::Detector::Description::DescriptionIO::
        Import<Detector::Description::ECAL>("../../../../simulation/MACE/PhaseI/SimMACEPhaseI/SimMACEPhaseI_geom.yaml");

    std::vector<std::string> files;
    for (auto i{1}; i < argc; ++i) { files.emplace_back(argv[i]); }
    // std::string fileName{argv[1]};
    // std::string filePath{"../../../../simulation/MACE/PhaseI/SimMACEPhaseI/"};

    const auto& ecal{Detector::Description::ECAL::Instance()};
    const auto& faceList{ecal.Mesh().fFaceList};
    const auto& clusterMap{ecal.Mesh().fClusterMap};

    std::map<int, CLHEP::Hep3Vector> centroidMap;

    for (int i{}; auto&& [centroid, _1, _2] : std::as_const(faceList)) {
        centroidMap[i] = centroid;
        i++;
    }

    TFile outputFile{Mustard::MPIX::ParallelizePath("output.root").generic_string().c_str(), "RECREATE"};
    using ECALEnergy = Mustard::Data::TupleModel<Mustard::Data::Value<float, "Edep", "Energy deposition">,
                                                 Mustard::Data::Value<float, "Edep1", "Energy deposition 1">,
                                                 Mustard::Data::Value<float, "Edep2", "Energy deposition 2">,
                                                 Mustard::Data::Value<float, "dE", "Delta energy">,
                                                 Mustard::Data::Value<double, "dt", "Delta time">,
                                                 Mustard::Data::Value<double, "theta", "angel">>;
    Mustard::Data::Output<ECALEnergy> reconEnergy{"G4Run0/ReconECAL"};

    Mustard::Data::Processor processor;
    processor.Process<Data::ECALSimHit>(
        ROOT::RDataFrame{"G4Run0/ECALSimHit", files}, "EvtID",
        [&](bool byPass, auto&& event) {
            if (byPass) { return; }
            muc::timsort(event,
                         [](auto&& hit1, auto&& hit2) {
                             return Get<"Edep">(*hit1) > Get<"Edep">(*hit2);
                         });
            std::unordered_map<short, std::shared_ptr<Mustard::Data::Tuple<Data::ECALSimHit>>> hitDict;
            std::vector<short> potentialSeedModule;

            for (auto&& hit : event) {
                hitDict.try_emplace(Get<"ModID">(*hit), hit);
                if (Get<"Edep">(*hit) < 15_MeV) { continue; }
                potentialSeedModule.emplace_back(Get<"ModID">(*hit));
            }

            if (std::ssize(potentialSeedModule) < 2) { return; }

            std::unordered_set<short> firstCluster;
            std::unordered_set<short> secondCluster;

            CLHEP::Hep3Vector firstCenter{};
            CLHEP::Hep3Vector secondCenter{};

            auto firstSeedModule = potentialSeedModule.begin();
            auto secondSeedModule = std::ranges::find_if(
                potentialSeedModule,
                [&](short m) { return centroidMap.at(*firstSeedModule).angle(centroidMap.at(m)) > 0.5 * pi; });
            if (secondSeedModule == potentialSeedModule.end()) { return; }

            const auto Clustering = [&](std::unordered_set<short>& set,
                                        CLHEP::Hep3Vector& c,
                                        std::vector<short>::iterator seedIt) {
                const auto addClusterLayers = [&](short module) {
                    set.insert(module);
                    for (auto&& neighbor : clusterMap.at(module)) {
                        set.insert(neighbor);
                        for (auto&& secondNeighbor : clusterMap.at(neighbor)) {
                            set.insert(secondNeighbor);
                            set.insert(clusterMap.at(secondNeighbor).begin(), clusterMap.at(secondNeighbor).end());
                        }
                    }
                };
                addClusterLayers(*seedIt);
                float totalEnergy{};
                CLHEP::Hep3Vector weightedCentroid{};

                for (const auto& module : set) {
                    auto hitIt = hitDict.find(module);
                    if (hitIt == hitDict.end() or Get<"Edep">(*hitIt->second) < 50_keV) { continue; }
                    float energy = Get<"Edep">(*hitIt->second);
                    weightedCentroid += energy * centroidMap.at(module);
                    totalEnergy += energy;
                }
                c = weightedCentroid / totalEnergy;
                return gRandom->Gaus(totalEnergy, 0.14 * std::sqrt(totalEnergy));
                // return totalEnergy;
            };

            auto firstClusterEnergy = Clustering(firstCluster, firstCenter, firstSeedModule);
            auto secondClusterEnergy = Clustering(secondCluster, secondCenter, secondSeedModule);

            if (firstClusterEnergy + secondClusterEnergy > muonium_mass_c2) { return; }

            Mustard::Data::Tuple<ECALEnergy> energyTuple;
            Get<"Edep">(energyTuple) = firstClusterEnergy + secondClusterEnergy;
            Get<"Edep1">(energyTuple) = firstClusterEnergy;
            Get<"Edep2">(energyTuple) = secondClusterEnergy;
            Get<"dE">(energyTuple) = std::abs(firstClusterEnergy - secondClusterEnergy);
            Get<"dt">(energyTuple) = std::abs(*Get<"t">(*hitDict.at(*firstSeedModule)) - *Get<"t">(*hitDict.at(*secondSeedModule)));
            Get<"theta">(energyTuple) = firstCenter.angle(secondCenter);
            reconEnergy.Fill(std::move(energyTuple));
        });

    reconEnergy.Write();

    return EXIT_SUCCESS;
}
