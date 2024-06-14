#include "MACE/Data/Output.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/Utility/ConvertGeometry.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.h++"

#include "TFile.h"
#include "TMacro.h"

#include "G4Run.hh"

#include "fmt/format.h"

#include <stdexcept>

namespace MACE::SimTarget {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimTarget_untitled"},
    fFileMode{"NEW"},
    fEnableYieldAnalysis{true},
    fThisRun{},
    fResultFile{},
    fMuoniumTrack{},
    fYieldFile{},
    fMessengerRegister{this} {}

Analysis::~Analysis() {
    Close();
}

auto Analysis::RunBegin(gsl::not_null<const G4Run*> run) -> void {
    fThisRun = run;
    const auto runID{fThisRun->GetRunID()};
    if (runID == 0) { Open(); }
    const auto runDirectory{fmt::format("G4Run{}", runID)};
    fResultFile->mkdir(runDirectory.c_str());
    fResultFile->cd(runDirectory.c_str());
}

auto Analysis::RunEnd() -> void {
    Write();
}

auto Analysis::Open() -> void {
    OpenResultFile();
    if (fEnableYieldAnalysis) {
        OpenYieldFile();
    }
}

auto Analysis::Write() -> void {
    WriteResult();
    if (fEnableYieldAnalysis) {
        AnalysisAndWriteYield();
    }
    fMuoniumTrack.clear();
}

auto Analysis::Close() -> void {
    CloseResultFile();
    if (fEnableYieldAnalysis) {
        CloseYieldFile();
    }
}

auto Analysis::OpenResultFile() -> void {
    const auto fullFilePath{MPIX::ParallelizePath(fFilePath).replace_extension(".root").generic_string()};
    fResultFile = TFile::Open(fullFilePath.c_str(), fFileMode.c_str(),
                              "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    if (fResultFile == nullptr) {
        throw std::runtime_error{fmt::format("MACE::SimTarget::Analysis::OpenResultFile: Cannot open file '{}' with mode '{}'",
                                             fullFilePath, fFileMode)};
    }
    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        Geant4X::ConvertGeometryToTMacro("SimTarget_gdml", "SimTarget.gdml")->Write();
    }
}

auto Analysis::WriteResult() -> void {
    Data::Output<MuoniumTrack> output{"MuoniumTrack"};
    output.Fill(fMuoniumTrack);
    output.Write();
}

auto Analysis::CloseResultFile() -> void {
    if (fResultFile == nullptr) { return; }
    fResultFile->Close();
    delete fResultFile;
}

auto Analysis::OpenYieldFile() -> void {
    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        fYieldFile = std::fopen(std::string{fFilePath}.append("_yield.csv").c_str(), "w");
        fmt::println(fYieldFile, "runID,nMuon,nMFormed,nMTargetDecay,nMVacuumDecay,nMDetectableDecay");
    }
}

auto Analysis::AnalysisAndWriteYield() -> void {
    std::array<unsigned long long, 5> yieldData;
    auto& [nMuon, nFormed, nTargetDecay, nVacuumDecay, nDetectableDecay]{yieldData};
    nMuon = static_cast<unsigned long long>(PrimaryGeneratorAction::Instance().NParticlePerEvent()) *
            static_cast<unsigned long long>(fThisRun->GetNumberOfEvent());
    nFormed = fMuoniumTrack.size();
    nTargetDecay = 0;
    nVacuumDecay = 0;
    nDetectableDecay = 0;

    const auto& target{Detector::Description::Target::Instance()};
    for (auto&& track : std::as_const(fMuoniumTrack)) {
        const auto& decayPosition{Get<"x">(*track).As<muc::array3d>()};
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

auto Analysis::CloseYieldFile() -> void {
    if (fYieldFile == nullptr) { return; }
    std::fclose(fYieldFile);
}

} // namespace MACE::SimTarget
