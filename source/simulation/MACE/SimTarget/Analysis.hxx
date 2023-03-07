#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Env/Memory/FreeSingleton.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"

#include "gsl/gsl"

#include <filesystem>
#include <fstream>
#include <memory>

class G4Run;

class TFile;

namespace MACE::SimTarget {

using Core::DataFactory;

class Analysis final : public Env::Memory::FreeSingleton<Analysis> {
public:
    Analysis();
    ~Analysis();

    void SetResultPath(const auto& path) { (fResultPath = std::forward<decltype(path)>(path)).replace_extension(); }
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
    DataFactory fDataFactory;
};

} // namespace MACE::SimTarget
