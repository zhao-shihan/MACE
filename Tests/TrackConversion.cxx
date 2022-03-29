#include "Core/DataModel/DataFactory.hxx"
#include "Core/DataModel/Track/HelixTrack.hxx"
#include "Core/DataModel/Track/PhysicsTrack.hxx"
#include "Utility/LiteralUnit.hxx"

#include "CLHEP/Units/PhysicalConstants.h"

using MACE::Core::DataModel::DataFactory;
using namespace MACE::Core::DataModel::Track;
using namespace MACE::Utility::LiteralUnit;

int main(int, char** argv) {
    DataFactory dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_Exact_");

    auto fileIn = TFile::Open(argv[1], "open");
    auto helixTree = dataHub.GetTree<HelixTrack>(*fileIn, 0);
    auto helixList = dataHub.CreateAndFillList<HelixTrack>(*helixTree);
    fileIn->Close();
    delete fileIn;

    std::vector<std::shared_ptr<PhysicsTrack>> trackList;
    std::vector<std::shared_ptr<HelixTrack>> revTrackList;
    std::vector<std::shared_ptr<HelixTrack>> diffList;
    trackList.reserve(helixList.size());
    revTrackList.reserve(helixList.size());
    diffList.reserve(helixList.size());
    for (auto&& helix : helixList) {
        const auto& physTrk = trackList.emplace_back(std::make_shared<PhysicsTrack>(*helix));
        const auto& revTrack = revTrackList.emplace_back(std::make_shared<HelixTrack>(*physTrk));
        auto& diff = diffList.emplace_back(std::make_shared<HelixTrack>());
        diff->SetVertexTime(revTrack->GetVertexTime() - helix->GetVertexTime());
        diff->SetCenter(revTrack->GetCenter() - helix->GetCenter());
        diff->SetRadius(revTrack->GetRadius() - helix->GetRadius());
        diff->SetZ0(revTrack->GetZ0() - helix->GetZ0());
        diff->SetAlpha(revTrack->GetAlpha() - helix->GetAlpha());
        diff->SetNumberOfFittedPoints(revTrack->GetNumberOfFittedPoints() - helix->GetNumberOfFittedPoints());
        diff->SetChi2(revTrack->GetChi2() - helix->GetChi2());
    }

    auto fileOut = TFile::Open(argv[2], "recreate");
    dataHub.SetPrefixFormatOfTreeName("Rep#_Conv_");
    dataHub.CreateAndFillTree<PhysicsTrack>(trackList, 0)->Write();
    dataHub.CreateAndFillTree<HelixTrack>(revTrackList, 0)->Write();
    dataHub.SetPrefixFormatOfTreeName("Rep#_Diff_");
    dataHub.CreateAndFillTree<HelixTrack>(diffList, 0)->Write();
    fileOut->Close();
    delete fileOut;

    return EXIT_SUCCESS;
}
