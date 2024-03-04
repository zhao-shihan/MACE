#include "MACE/Data/Output.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.h++"

#include "TFile.h"

#include "G4Run.hh"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimTarget {

Analysis::Analysis() :
    PassiveSingleton(),
    fResultPath{"SimTarget_result"},
    fEnableYieldAnalysis{true},
    fThisRun{},
    fResultFile{},
    fMuoniumTrack{},
    fYieldFile{},
    fMessengerRegister{this} {}

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
    fMuoniumTrack.clear();
}

void Analysis::Close() {
    CloseResultFile();
    if (fEnableYieldAnalysis) {
        CloseYieldFile();
    }
}

void Analysis::OpenResultFile() {
    const auto fullResultPath{MPIX::ParallelizePath(fResultPath, ".root").generic_string()};
    fResultFile = TFile::Open(fullResultPath.c_str(), "RECREATE",
                              "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fResultFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimTarget::Analysis::OpenResultFile: Cannot open file \"{}\"", fullResultPath)};
    }
}

void Analysis::WriteResult() {
    Data::Output<MuoniumTrack> output{fmt::format("G4Run{}_MTrk", fThisRun->GetRunID())};
    output << fMuoniumTrack;
    output.Write();
}

void Analysis::CloseResultFile() {
    if (fResultFile == nullptr) { return; }
    fResultFile->Close();
    delete fResultFile;
}

void Analysis::OpenYieldFile() {
    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        fYieldFile = std::fopen(std::string{fResultPath}.append("_yield.csv").c_str(), "w");
        fmt::println(fYieldFile, "runID,nMuon,nMFormed,nMTargetDecay,nMVacuumDecay,nMDetectableDecay");
    }
}

void Analysis::AnalysisAndWriteYield() {
    std::array<unsigned long long, 5> yieldData;
    auto& [nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay]{yieldData};
    nMuon = static_cast<unsigned long long>(PrimaryGeneratorAction::Instance().PrimariesForEachG4Event()) *
            static_cast<unsigned long long>(fThisRun->GetNumberOfEvent());
    nFormed = fMuoniumTrack.size();
    nTargetDecay = 0;
    nVacuumDecay = 0;
    nDetectableDecay = 0;

    const auto& target{Detector::Description::Target::Instance()};
    for (auto&& track : std::as_const(fMuoniumTrack)) {
        const auto& decayPosition{Get<"x">(*track).As<stdx::array3d>()};
        if (target.Contain(decayPosition)) {
            ++nTargetDecay;
        } else {
            ++nVacuumDecay;
            if (target.DetectableAt(decayPosition)) {
                ++nDetectableDecay;
            }
        }
    }

    if (const auto& mpiEnv{Env::MPIEnv::Instance()};
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
            fmt::println(fYieldFile, "{},{},{},{},{},{}", fThisRun->GetRunID(), nMuonTotal, nFormedTotal, nTargetDecayTotal, nVacuumDecayTotal, nDetectableDecayTotal);
        }
    } else {
        fmt::println(fYieldFile, "{},{},{},{},{},{}", fThisRun->GetRunID(), nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay);
    }
}

void Analysis::CloseYieldFile() {
    if (fYieldFile == nullptr) { return; }
    std::fclose(fYieldFile);
}

} // namespace MACE::SimTarget
