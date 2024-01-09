#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.h++"
#include "MACE/Extension/MPIX/MakeMPIFilePath.h++"

#include "TFile.h"

#include "G4Run.hh"

namespace MACE::SimTarget {

Analysis::Analysis() :
    PassiveSingleton(),
    fResultPath{"SimTarget_result"},
    fEnableYieldAnalysis{true},
    fThisRun{},
    fMuoniumTrackList{},
    fResultFile{},
    fYieldFile{},
    fDataFactory{} {
    AnalysisMessenger::Instance().AssignTo(this);
    fDataFactory.TreeNamePrefixFormat("Run{}_");
}

Analysis::~Analysis() {
    Close();
}

void Analysis::RunBegin(gsl::not_null<const G4Run*> run) {
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
        MPIX::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
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
    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        const auto yieldPath = std::filesystem::path(fResultPath).concat("_yield.csv");
        fYieldFile = std::make_unique<std::ofstream>(yieldPath, std::ios::out);
        *fYieldFile << "runID,nMuon,nMFormed,nMTargetDecay,nMVacuumDecay,nMDetectableDecay" << std::endl;
    }
}

void Analysis::AnalysisAndWriteYield() {
    std::array<unsigned long long, 5> yieldData;
    auto& [nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay] = yieldData;
    nMuon = static_cast<unsigned long long>(PrimaryGeneratorAction::Instance().MuonsForEachG4Event()) *
            static_cast<unsigned long long>(fThisRun->GetNumberOfEvent());
    nFormed = fMuoniumTrackList.size();
    nTargetDecay = 0;
    nVacuumDecay = 0;
    nDetectableDecay = 0;

    const auto& target = Detector::Description::Target::Instance();
    for (auto&& track : std::as_const(fMuoniumTrackList)) {
        const auto& decayPosition = track->DecayPosition();
        if (target.Contain(decayPosition)) {
            ++nTargetDecay;
        } else {
            ++nVacuumDecay;
            if (target.TestDetectable(decayPosition)) {
                ++nDetectableDecay;
            }
        }
    }

    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        mpiEnv.Parallel()) {
        std::vector<std::array<unsigned long long, 5>> yieldDataRecv;
        if (mpiEnv.OnCommWorldMaster()) { yieldDataRecv.resize(mpiEnv.CommWorldSize()); }
        MPI_Gather(yieldData.data(),       // sendbuf
                   yieldData.size(),       // sendcount
                   MPI_UNSIGNED_LONG_LONG, // sendtype
                   yieldDataRecv.data(),   // recvbuf
                   yieldData.size(),       // recvcount
                   MPI_UNSIGNED_LONG_LONG, // recvtype
                   0,                      // root
                   MPI_COMM_WORLD);        // comm

        if (mpiEnv.OnCommWorldMaster()) {
            auto nMuonTotal{0ull};
            auto nFormedTotal{0ull};
            auto nTargetDecayTotal{0ull};
            auto nVacuumDecayTotal{0ull};
            auto nDetectableDecayTotal{0ull};
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
