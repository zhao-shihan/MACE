#include "MACE/Simulation/SimTarget/Analysis.hxx"
#include "MACE/Simulation/SimTarget/Messenger/AnalysisMessenger.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"
#include "MACE/Utility/MPITool/MakeMPIFilePath.hxx"

namespace MACE::Simulation::SimTarget {

Analysis& Analysis::Instance() {
    static Analysis instance;
    return instance;
}

Analysis::Analysis() :
    fTarget(std::addressof(Target::Instance())),
    fResultName("SimTarget_result"),
    fEnableYieldAnalysis(true),
    fDetectableRegion(ConstructFormula("abs(x)>30 || abs(y)>30 || z>0")),
    fThisRun(nullptr),
    fMuoniumTrackList(0),
    fResultFile(nullptr),
    fYieldFile(nullptr),
    fDataFactory() {
    Messenger::AnalysisMessenger::Instance();
    fDataFactory.SetTreeNamePrefixFormat("Run#_");
}

void Analysis::RunBegin(ObserverPtr<const G4Run> run) {
    fThisRun = run;
    if (fThisRun->GetRunID() == 0) {
        Open();
    }
}

void Analysis::RunEnd() {
    Write();
}

void Analysis::G4Quit() {
    Close();
}

void Analysis::Open() {
    OpenResultFile();
    if (fEnableYieldAnalysis) {
        OpenYieldFile();
    }
}

void Analysis::Write() {
    WriteResult();
    if (fEnableYieldAnalysis) {
        AnalysisAndWriteYield();
    }
    fMuoniumTrackList.clear();
}

void Analysis::Close() {
    CloseResultFile();
    if (fEnableYieldAnalysis) {
        CloseYieldFile();
    }
}

void Analysis::OpenResultFile() {
    const auto filePath = MACE::Utility::MPITool::MakeMPIFilePath(fResultName, ".root");
    fResultFile = std::make_unique<TFile>(filePath.c_str(), "recreate");
}

void Analysis::WriteResult() {
    if (fMuoniumTrackList.empty()) { return; }
    fDataFactory.CreateAndFillTree<MuoniumTrack>(fMuoniumTrackList, fThisRun->GetRunID())->Write();
}

void Analysis::CloseResultFile() {
    if (fResultFile == nullptr) { return; }
    fResultFile->Close();
    fResultFile.reset();
}

void Analysis::OpenYieldFile() {
    if (RunManager::GetRunManager()->GetCommRank() == 0) {
        fYieldFile = std::make_unique<std::ofstream>(fResultName + "_yield.csv", std::ios::out);
        *fYieldFile << "runID,nMuon,nMFormed,nMTargetDecay,nMVacuumDecay,nMDetectableDecay" << std::endl;
    }
}

void Analysis::AnalysisAndWriteYield() {
    std::array<unsigned long, 5> yieldData;
    auto& [nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay] = yieldData;
    nMuon = (unsigned long)RunManager::Instance().GetPrimaryGeneratorAction().GetMuonsForEachG4Event() * (unsigned long)fThisRun->GetNumberOfEvent();
    nFormed = fMuoniumTrackList.size();
    nTargetDecay = 0;
    nVacuumDecay = 0;
    nDetectableDecay = 0;

    for (auto&& track : std::as_const(fMuoniumTrackList)) {
        const auto& decayPosition = track->GetDecayPosition();
        if (fTarget->Contains(decayPosition.data())) {
            ++nTargetDecay;
        } else {
            ++nVacuumDecay;
            if (IsDetectable(decayPosition.data())) {
                ++nDetectableDecay;
            }
        }
    }

    const auto commSize = RunManager::GetRunManager()->GetCommSize();
    if (commSize > 1) {
        const auto commRank = RunManager::GetRunManager()->GetCommRank();

        std::vector<decltype(yieldData)> yieldDataRecv;
        if (commRank == 0) { yieldDataRecv.resize(commSize); }
        MPI_Gather(yieldData.data(), yieldData.size(), MPI_UNSIGNED_LONG, yieldDataRecv.data(), yieldData.size(), MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

        if (commRank == 0) {
            unsigned long nMuonTotal = 0;
            unsigned long nFormedTotal = 0;
            unsigned long nTargetDecayTotal = 0;
            unsigned long nVacuumDecayTotal = 0;
            unsigned long nDetectableDecayTotal = 0;
            for (auto&& [nMuonRecv, nFormedRecv, nTargetDecayRecv, nVacuumDecayRecv, nDetectableDecayRecv] : std::as_const(yieldDataRecv)) {
                nMuonTotal += nMuonRecv;
                nFormedTotal += nFormedRecv;
                nTargetDecayTotal += nTargetDecayRecv;
                nVacuumDecayTotal += nVacuumDecayRecv;
                nDetectableDecayTotal += nDetectableDecayRecv;
            }
            *fYieldFile << fThisRun->GetRunID() << ',' << nMuonTotal << ',' << nFormedTotal << ',' << nTargetDecayTotal << ',' << nVacuumDecayTotal << ',' << nDetectableDecayTotal << std::endl;
        }
    } else {
        *fYieldFile << fThisRun->GetRunID() << ',' << nMuon << ',' << nFormed << ',' << nTargetDecay << ',' << nVacuumDecay << ',' << nDetectableDecay << std::endl;
    }
}

void Analysis::CloseYieldFile() {
    if (fYieldFile == nullptr) { return; }
    fYieldFile->close();
    fYieldFile.reset();
}

} // namespace MACE::Simulation::SimTarget
