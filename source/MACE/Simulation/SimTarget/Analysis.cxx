// #include "MACE/Simulation/SimTarget/Messenger/AnalysisMessenger.hxx"
#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4MPImanager.hh"

namespace MACE::Simulation::SimTarget {

// using Messenger::AnalysisMessenger;

Analysis& Analysis::Instance() {
    static Analysis instance;
    return instance;
}

Analysis::Analysis() :
    fFile(nullptr),
    fMPIFileTools(nullptr),
    fMuoniumTrackList(0),
    fDataFactory() {
    // AnalysisMessenger::Instance();
    MPIFileTools::SetOutStream(G4cout);
    fDataFactory.SetTreeNamePrefixFormat("Run#_");
}

void Analysis::Open(Option_t* option) {
    if (MPI::Is_initialized()) {
        fMPIFileTools = std::make_unique<MPIFileTools>(fResultName, ".root", *G4MPImanager::GetManager()->GetComm());
    } else {
        fMPIFileTools = std::make_unique<MPIFileTools>(fResultName, ".root");
    }
    fFile = std::make_unique<TFile>(fMPIFileTools->GetFilePath().c_str(), option);
}

void Analysis::Write(G4int runID) {
    if (fMuoniumTrackList.empty()) { return; }
    fDataFactory.CreateAndFillTree<MuoniumTrack>(fMuoniumTrackList, runID)->Write();
    fMuoniumTrackList.clear();
}

void Analysis::Close(Option_t* option) {
    fFile->Close(option);
    fFile.reset();
}

int Analysis::Merge(G4bool forced) {
    if (fMPIFileTools) {
        return fMPIFileTools->MergeRootFiles(forced);
    } else {
        return MPIFileTools::MergeRootFilesViaFilesMap(fResultName, forced);
    }
}

} // namespace MACE::Simulation::SimTarget
