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

    void ResultPath(auto&& path) { (fResultPath = std::forward<decltype(path)>(path)).replace_extension(); }
    void EnableYieldAnalysis(bool val) { fEnableYieldAnalysis = val; }

    void RunBegin(gsl::not_null<const G4Run*> run);
    auto NewMuoniumTrack() { return fMuoniumTrackList.emplace_back(std::make_unique_for_overwrite<MuoniumTrack>()).get(); }
    void RunEnd();

private:
    void Open();
    void Write();
    void Close();

    void OpenResultFile();
    void WriteResult();
    void CloseResultFile();

    void OpenYieldFile();
    void AnalysisAndWriteYield();
    void CloseYieldFile();

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
