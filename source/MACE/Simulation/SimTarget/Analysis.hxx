#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Simulation/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Run.hh"

#include "TFile.h"

namespace MACE::Simulation::SimTarget {

using Core::DataFactory;
using Core::Geometry::Description::Target;
using Utility::ObserverPtr;

class Analysis final {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetResultName(std::string_view resultName) { fResultName = resultName; }
    void EnableYieldAnalysis(G4bool val) { fEnableYieldAnalysis = val; }

    void RunBegin(ObserverPtr<const G4Run> run);
    auto NewMuoniumTrack() { return fMuoniumTrackList.emplace_back(std::make_unique<MuoniumTrack>()).get(); }
    void RunEnd();
    void G4Quit();

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
    const ObserverPtr<const Target> fTarget;
    std::string fResultName;
    G4bool fEnableYieldAnalysis;

    ObserverPtr<const G4Run> fThisRun;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;

    std::unique_ptr<TFile> fResultFile;
    std::unique_ptr<std::ofstream> fYieldFile;
    DataFactory fDataFactory;
};

} // namespace MACE::Simulation::SimTarget
