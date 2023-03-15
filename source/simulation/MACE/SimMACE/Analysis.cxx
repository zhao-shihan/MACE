#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Hit/CDCHit.hxx"
#include "MACE/SimMACE/Hit/EMCalHit.hxx"
#include "MACE/SimMACE/Hit/MCPHit.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include "TFile.h"

namespace MACE::SimMACE {

Analysis::Analysis() :
    FreeSingleton(),
    fFile(nullptr),
    fResultPath("SimMACE_untitled"),
    fEnableCoincidenceOfEMCal(true),
    fEnableCoincidenceOfMCP(true),
    fDataHub(),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance().AssignTo(this);
}

void Analysis::Open(Option_t* option) {
    fFile = new TFile(MPIUtil::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
                      option,
                      "",
                      ROOT::RCompressionSetting::EDefaults::kUseSmallest);
}

void Analysis::Close(Option_t* option) {
    fFile->Close(option);
    delete fFile;
}

void Analysis::WriteEvent() {
    const auto emCalTriggered = not fEnableCoincidenceOfEMCal or fEMCalHitList->size() > 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or fMCPHitList->size() > 0;
    const auto cdcTriggered = fCDCHitList->size() > 0;
    // if coincident then write their data
    if (emCalTriggered and mcpTriggered and cdcTriggered) {
        using namespace DataModel::SimHit;
        // create trees
        const auto emCalHitTree = fDataHub.CreateTree<EMCalSimHit>();
        const auto mcpHitTree = fDataHub.CreateTree<MCPSimHit>();
        const auto cdcHitTree = fDataHub.CreateTree<CDCSimHit>();
        // fill trees
        fDataHub.FillTree(*fEMCalHitList, *emCalHitTree, true);
        fDataHub.FillTree(*fMCPHitList, *mcpHitTree, true);
        fDataHub.FillTree(*fCDCHitList, *cdcHitTree, true);
        // write trees
        emCalHitTree->Write();
        mcpHitTree->Write();
        cdcHitTree->Write();
    }
}

} // namespace MACE::SimMACE
