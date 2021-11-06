#include <unordered_map>

#include "TH2I.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "DataModel/PersistencyReader.hh"
#include "Reconstruction/Recognizer/HoughCartesian.hh"
#include "Reconstruction/Recognizer/HoughPolar.hh"
#include "Reconstruction/Fitter/Kalman.hh"
#include "SimG4/Hit/SpectrometerHit.hh"

using namespace MACE;

int main(int, char** argv) {
    using Hit = SimG4::Hit::SpectrometerHit;

    DataModel::PersistencyReader reader(argv[1]);
    // Reconstruction::Recognizer::HoughCartesian<Hit> recognizer(2500, std::stol(argv[2]), 500);
    Reconstruction::Recognizer::HoughPolar<Hit> recognizer(350, 5000, std::stol(argv[2]), std::stol(argv[3]));
    recognizer.EnableHoughSpaceVisualization(true);
    auto hitList = reader.CreateListFromTree<Hit>();
    recognizer.SetEventToBeRecognized(hitList);
    recognizer.Recognize();
    const auto& recognized = recognizer.GetRecognizedTrackList();
    recognizer.SaveLastRecognition("recognition.root");
    reader.Close();

    Reconstruction::Fitter::Kalman<Hit> fitter("MACEGeometry.gdml");
    fitter.Fit(recognized);
    fitter.OpenDisplay();

    /* DataModel::PersistencyReader reader;

    for (int res = 100; res <= 1000; res += 10) {
        Reconstruction::Recognizer::HoughCartesian<Hit> recognizer(2500, res, 500);
        // Reconstruction::Recognizer::HoughPolar<Hit> recognizer(350, 5000, res, res);

        reader.Open(argv[1]);
        auto hitList = reader.CreateListFromTree<Hit>();
        reader.Close();

        std::unordered_map<Int_t, std::vector<const Hit*>> trueTrackMap;
        for (auto&& hit : hitList) {
            auto [trackIt, newTrack] = trueTrackMap.emplace(hit->GetTrackID(), 0);
            if (newTrack) {
                trackIt->second.reserve(32);
            }
            trackIt->second.emplace_back(hit.get());
        }
        Int_t trackCount = 0;
        for (auto&& track : trueTrackMap) {
            if (track.second.size() >= 13) { ++trackCount; }
        }

        recognizer.SetEventToBeRecognized(hitList);
        recognizer.Recognize();
        const auto& recognized = recognizer.GetRecognizedTrackList();
        Double_t trackErrorRate = 0.0;
        Double_t chargeErrorRate = 0.0;
        for (auto&& [recoTrack, center] : recognized) {
            std::unordered_map<Int_t, std::vector<const Hit*>> recognizedTrackMap;
            for (auto&& recoHit : recoTrack) {
                auto [trackIt, newTrack] = recognizedTrackMap.emplace(recoHit->GetTrackID(), 0);
                if (newTrack) {
                    trackIt->second.reserve(32);
                }
                trackIt->second.emplace_back(recoHit.get());
            }
            auto exactTrack = std::max_element(recognizedTrackMap.cbegin(), recognizedTrackMap.cend(),
                [](const auto& left, const auto& right) {
                    return left.second.size() < right.second.size();
                }
            )->second;
            trackErrorRate += 1.0 - (double_t)exactTrack.size() / (double_t)recoTrack.size();

            auto truePDGCode = exactTrack.front()->GetParticlePDGCode();
            auto hitCrossCenter = exactTrack.front()->GetHitPosition().fX * center.second - center.first * exactTrack.front()->GetHitPosition().fY;
            auto pdgCode = (hitCrossCenter > 0) ? (11) : (-11); // cross>0 => e-(11), cross<0 => e+(-11)
            if (truePDGCode != pdgCode) { chargeErrorRate += 1.0; }
        }
        trackErrorRate /= recognized.size();
        chargeErrorRate /= recognized.size();

        std::cout << trackCount << ',' << res << ',' << (double_t)recognized.size() / (double_t)trackCount << ',' << trackErrorRate * 15 << ',' << chargeErrorRate << std::endl;
    } */
}