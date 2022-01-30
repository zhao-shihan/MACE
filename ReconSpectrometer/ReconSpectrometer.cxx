#include <unordered_map>
#include <iostream>

#include "TH2I.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMarker.h"

#include "DataModel/PersistencyReader.hxx"
#include "DataModel/PersistencyWriter.hxx"
#include "ReconSpectrometer/Reconstructor/Hough.hxx"
#include "ReconSpectrometer/Fitter/DirectLeastChiSquare.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"

using namespace MACE::ReconSpectrometer;
using namespace MACE::DataModel;

int main(int, char** argv) {
    using Hit_t = MACE::SimMACE::Hit::SpectrometerHit;

    PersistencyReader reader(argv[1]);
    Reconstructor::Hough<Fitter::DirectLeastChiSquare, Hit_t> reconstructor(350, 5000, std::stol(argv[2]), std::stol(argv[3]), -50, 150, std::stol(argv[4]), std::stol(argv[5]));
    auto event = reader.CreateListFromTree<Hit_t>();
    reader.Close();

    reconstructor.SetHitDataToBeRecongnized(event);
    reconstructor.Reconstruct();
    const auto& recognized = reconstructor.GetRecognizedTrackList();

    PersistencyWriter writer(TString("reconed_") + argv[1]);
    for (auto&& [recogParameter, recogTrack] : recognized) {
        writer.CreateTreeFromList<Hit_t>(recogTrack);
    }
    writer.WriteTrees();
    writer.Close();

    /* PersistencyReader reader;

    for (int res = 100; res <= 1000; res += 10) {
        Reconstructor::Hough<Hit_t> reconstructor(350, 5000, res, res, -50, 200, res, res);

        reader.Open(argv[1]);
        auto event = reader.CreateListFromTree<Hit_t>();
        reader.Close();

        std::unordered_map<Int_t, std::vector<std::shared_ptr<Hit_t>>> trueTrackMap;
        for (auto&& hit : event) {
            auto [trackIt, isNewTrack] = trueTrackMap.emplace(hit->GetTrackID(), 0);
            if (isNewTrack) {
                trackIt->second.reserve(32);
            }
            trackIt->second.emplace_back(hit);
        }
        Int_t trackCount = 0;
        for (auto&& track : trueTrackMap) {
            if (track.second.size() >= 13) { ++trackCount; }
        }

        reconstructor.Recognize(event);
        const auto& recognized = reconstructor.GetRecognizedTrackList();
        const auto& parameters = reconstructor.GetRecognizedParameterList();
        double trackErrorRate = 0.0;
        double chargeErrorRate = 0.0;
        for (size_t i = 0; i < recognized.size(); ++i) {
            const auto& recoTrack = recognized[i];
            auto center = std::make_pair(std::get<0>(parameters[i]), std::get<1>(parameters[i]));
            std::unordered_map<Int_t, std::vector<std::shared_ptr<Hit_t>>> recognizedTrackMap;
            for (auto&& recoHit : recoTrack) {
                auto [trackIt, isNewTrack] = recognizedTrackMap.emplace(recoHit->GetTrackID(), 0);
                if (isNewTrack) {
                    trackIt->second.reserve(32);
                }
                trackIt->second.emplace_back(recoHit);
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