#include "DataModel/DataHub.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"
#include "LiteralUnit.hxx"

#include "CLHEP/Units/PhysicalConstants.h"

using MACE::Core::DataModel::DataHub;
using namespace MACE::Core::DataModel::Track;
using namespace MACE::Utility::LiteralUnit;

int main(int, char** argv) {
    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");

    auto fileIn = TFile::Open(argv[1], "open");
    auto helixTree = dataHub.GetTree<HelixTrack>(*fileIn, 0);
    auto helixList = dataHub.CreateAndFillList<HelixTrack>(*helixTree);
    fileIn->Close();
    delete fileIn;

    std::vector<std::shared_ptr<PhysicsTrack>> trackList;
    trackList.reserve(helixList.size());
    for (auto&& helix : helixList) {
        trackList.emplace_back(std::make_shared<PhysicsTrack>(*helix, 0.1_T, CLHEP::electron_mass_c2));
    }

    auto fileOut = TFile::Open(argv[2], "recreate");
    auto trackTree = dataHub.CreateAndFillTree<PhysicsTrack>(trackList, 0);
    trackTree->Write();
    fileOut->Close();
    delete fileOut;

    return EXIT_SUCCESS;
}
