#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include "G4Run.hh"

#include "TFile.h"

namespace MACE::SimTarget {

Analysis::Analysis() :
    FreeSingleton<Analysis>(),
    fResultPath("SimTarget_result"),
    fEnableYieldAnalysis(true),
    fThisRun(nullptr),
    fMuoniumTrackList(0),
    fResultFile(nullptr),
    fYieldFile(nullptr),
    fDataFactory() {
    Messenger::AnalysisMessenger::Instance().SetTo(this);
    fDataFactory.TreeNamePrefixFormat("Run#_");
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
        Utility::MPIUtil::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
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
    if (Environment::MPIEnvironment::Instance().IsMaster()) {
        const auto yieldPath = std::filesystem::path(fResultPath).concat("_yield.csv");
        fYieldFile = std::make_unique<std::ofstream>(yieldPath, std::ios::out);
        *fYieldFile << "runID,nMuon,nMFormed,nMTargetDecay,nMVacuumDecay,nMDetectableDecay" << std::endl;
    }
}

void Analysis::AnalysisAndWriteYield() {
    std::array<unsigned long, 5> yieldData;
    auto& [nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay] = yieldData;
    nMuon = static_cast<unsigned long>(RunManager::Instance().GetPrimaryGeneratorAction().GetMuonsForEachG4Event()) *
            static_cast<unsigned long>(fThisRun->GetNumberOfEvent());
    nFormed = static_cast<unsigned long>(fMuoniumTrackList.size());
    nTargetDecay = 0;
    nVacuumDecay = 0;
    nDetectableDecay = 0;

    const auto& target = Core::Geometry::Description::Target::Instance();
    for (auto&& track : std::as_const(fMuoniumTrackList)) {
        const auto& decayPosition = track->GetDecayPosition();
        if (target.Contain(decayPosition)) {
            ++nTargetDecay;
        } else {
            ++nVacuumDecay;
            if (target.TestDetectable(decayPosition)) {
                ++nDetectableDecay;
            }
        }
    }

    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsParallel()) {
        std::vector<decltype(yieldData)> yieldDataRecv;
        if (mpiEnv.IsMaster()) { yieldDataRecv.resize(mpiEnv.GetWorldSize()); }
        MACE_CHECKED_MPI_CALL(MPI_Gather,
                              yieldData.data(),
                              yieldData.size(),
                              MPI_UNSIGNED_LONG,
                              yieldDataRecv.data(),
                              yieldData.size(),
                              MPI_UNSIGNED_LONG,
                              0,
                              MPI_COMM_WORLD)

        if (mpiEnv.IsMaster()) {
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
