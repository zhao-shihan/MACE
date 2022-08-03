#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"
#include "MACE/Utility/UtilMPI/CheckedMPICall.hxx"
#include "MACE/Utility/UtilMPI/MakeMPIFilePath.hxx"

#include "G4Run.hh"

#include "TFile.h"

namespace MACE::SimTarget {

using MACE::Environment::MPIEnvironment;

Analysis::Analysis() :
    NonMoveableBase(),
    fResultName("SimTarget_result"),
    fEnableYieldAnalysis(true),
    fThisRun(nullptr),
    fMuoniumTrackList(0),
    fResultFile(nullptr),
    fYieldFile(nullptr),
    fDataFactory() {
    Messenger::AnalysisMessenger::Instance().SetTo(this);
    fDataFactory.SetTreeNamePrefixFormat("Run#_");
}

Analysis::~Analysis() {
    Close();
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
    fResultFile = std::make_unique<TFile>(
        MACE::Utility::UtilMPI::MakeMPIFilePath(fResultName, ".root").generic_string().c_str(),
        "recreate");
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
    if (MPIEnvironment::IsMaster()) {
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

    const auto& target = Core::Geometry::Description::Target::Instance();
    for (auto&& track : std::as_const(fMuoniumTrackList)) {
        const auto& decayPosition = track->GetDecayPosition();
        if (target.Contains(decayPosition)) {
            ++nTargetDecay;
        } else {
            ++nVacuumDecay;
            if (target.TestDetectable(decayPosition)) {
                ++nDetectableDecay;
            }
        }
    }

    if (MPIEnvironment::IsParallel()) {
        std::vector<decltype(yieldData)> yieldDataRecv;
        if (MPIEnvironment::IsMaster()) { yieldDataRecv.resize(MPIEnvironment::WorldCommSize()); }
        MACE_CHECKED_MPI_CALL(MPI_Gather, yieldData.data(), yieldData.size(), MPI_UNSIGNED_LONG, yieldDataRecv.data(), yieldData.size(), MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD)

        if (MPIEnvironment::IsMaster()) {
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

} // namespace MACE::SimTarget
