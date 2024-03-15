#pragma once

#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.h++"

#include "gsl/gsl"

#include <cstdio>
#include <filesystem>
#include <memory>
#include <vector>

class G4Run;

class TFile;

namespace MACE::SimTarget {

using MuoniumTrack = Data::TupleModel<Data::Value<int, "EvtID", "Event ID">,
                                      Data::Value<int, "TrkID", "Track ID">,
                                      Data::Value<int, "PDGID", "Particle PDG ID">,
                                      Data::Value<float, "t0", "Vertex time">,
                                      Data::Value<stdx::array3f, "x0", "Vertex position">,
                                      Data::Value<float, "Ek0", "Vertex kinetic energy">,
                                      Data::Value<stdx::array3f, "p0", "Vertex momentum">,
                                      Data::Value<double, "t", "Decay time">,
                                      Data::Value<stdx::array3f, "x", "Decay position">,
                                      Data::Value<float, "Ek", "Kinetic energy just before decay">,
                                      Data::Value<stdx::array3f, "p", "Momentum just before decay">>;

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();
    ~Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path.replace_extension()); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto EnableYieldAnalysis(bool val) -> void { fEnableYieldAnalysis = val; }

    void RunBegin(gsl::not_null<const G4Run*> run);
    auto NewMuoniumTrack() { return fMuoniumTrack.emplace_back(std::make_unique_for_overwrite<Data::Tuple<MuoniumTrack>>()).get(); }
    void RunEnd();

private:
    auto Open() -> void;
    auto Write() -> void;
    auto Close() -> void;

    auto OpenResultFile() -> void;
    auto WriteResult() -> void;
    auto CloseResultFile() -> void;

    auto OpenYieldFile() -> void;
    auto AnalysisAndWriteYield() -> void;
    auto CloseYieldFile() -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    bool fEnableYieldAnalysis;

    const G4Run* fThisRun;

    gsl::owner<TFile*> fResultFile;
    std::vector<std::unique_ptr<Data::Tuple<MuoniumTrack>>> fMuoniumTrack;

    gsl::owner<std::FILE*> fYieldFile;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimTarget
