#pragma once

#include "MACE/DataModel/DataFactory.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimTarget/MuoniumTrack.h++"

#include "gsl/gsl"

#include <filesystem>
#include <fstream>
#include <memory>

class G4Run;

class TFile;

namespace MACE::SimTarget {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();
    ~Analysis();

    auto ResultPath(std::filesystem::path path) -> void { fResultPath = std::move(path.replace_extension()); }
    auto EnableYieldAnalysis(bool val) -> void { fEnableYieldAnalysis = val; }

    void RunBegin(gsl::not_null<const G4Run*> run);
    auto NewMuoniumTrack() { return fMuoniumTrackList.emplace_back(std::make_unique_for_overwrite<MuoniumTrack>()).get(); }
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
    std::filesystem::path fResultPath;
    bool fEnableYieldAnalysis;

    const G4Run* fThisRun;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;

    std::unique_ptr<TFile> fResultFile;
    std::unique_ptr<std::ofstream> fYieldFile;
    DataModel::DataFactory fDataFactory;
};

} // namespace MACE::SimTarget
