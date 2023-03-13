#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/VectorArithmetic.hxx"

#include "CLHEP/Units/PhysicalConstants.h"

using MACE::DataModel::DataFactory;
using namespace MACE::DataModel::Track;
using namespace MACE::LiteralUnit;
using namespace MACE::VectorArithmetic::Vector2Arithmetic;

int main(int, char* argv[]) {
    DataFactory dataHub;
    dataHub.TreeNamePrefixFormat("Rep{}_Exact_");

    auto fileIn = TFile::Open(argv[1], "open");
    auto helixTree = dataHub.FindTree<CDCHelixTrack>(*fileIn, 0);
    auto helixList = dataHub.CreateAndFillList<CDCHelixTrack>(*helixTree);
    fileIn->Close();
    delete fileIn;

    std::vector<std::shared_ptr<CDCPhysicsTrack>> trackList;
    std::vector<std::shared_ptr<CDCHelixTrack>> revTrackList;
    std::vector<std::shared_ptr<CDCHelixTrack>> diffList;
    trackList.reserve(helixList.size());
    revTrackList.reserve(helixList.size());
    diffList.reserve(helixList.size());
    for (auto&& helix : helixList) {
        const auto& physTrk = trackList.emplace_back(std::make_shared<CDCPhysicsTrack>(*helix));
        const auto& revTrack = revTrackList.emplace_back(std::make_shared<CDCHelixTrack>(*physTrk));
        auto& diff = diffList.emplace_back(std::make_shared<CDCHelixTrack>());
        diff->VertexTime(revTrack->VertexTime() - helix->VertexTime());
        diff->SetCenter(revTrack->GetCenter() - helix->GetCenter());
        diff->Radius(revTrack->Radius() - helix->Radius());
        diff->SetZ0(revTrack->GetZ0() - helix->GetZ0());
        diff->SetAlpha(revTrack->GetAlpha() - helix->GetAlpha());
        diff->SetNumHits(revTrack->GetNumHits() - helix->GetNumHits());
        diff->SetChi2(revTrack->GetChi2() - helix->GetChi2());
    }

    auto fileOut = TFile::Open(argv[2], "recreate");
    dataHub.TreeNamePrefixFormat("Rep{}_Conv_");
    dataHub.CreateAndFillTree<CDCPhysicsTrack>(trackList, 0)->Write();
    dataHub.CreateAndFillTree<CDCHelixTrack>(revTrackList, 0)->Write();
    dataHub.TreeNamePrefixFormat("Rep{}_Diff_");
    dataHub.CreateAndFillTree<CDCHelixTrack>(diffList, 0)->Write();
    fileOut->Close();
    delete fileOut;

    return EXIT_SUCCESS;
}
