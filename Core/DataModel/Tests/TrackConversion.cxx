#include "CLHEP/Units/PhysicalConstants.h"

#include "DataModel/DataHub.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"
#include "LiteralUnits.hxx"

using namespace MACE::DataModel;
using MACE::operator""_T;
using MACE::operator""_keV;

int main(int, char** argv) {
    DataHub dataHub;
    dataHub.SetPrefixFormatOfTreeName("Rep#_");

    auto fileIn = TFile::Open(argv[1], "open");
    auto helixTree = dataHub.GetTree<HelixTrack>(*fileIn);
    auto helixList = dataHub.CreateAndFillList<HelixTrack>(*helixTree);
    fileIn->Close();
    delete fileIn;

    std::vector<std::shared_ptr<PhysicsTrack>> trackList;
    trackList.reserve(helixList.size());
    for (auto&& helix : helixList) {
        trackList.emplace_back(std::make_shared<PhysicsTrack>(*helix, 1, 0.1_T, CLHEP::electron_mass_c2));
    }

    auto fileOut = TFile::Open(argv[2], "recreate");
    auto trackTree = dataHub.CreateAndFillTree<PhysicsTrack>(trackList);
    trackTree->Write();
    fileOut->Close();
    delete fileOut;

    return EXIT_SUCCESS;
}
