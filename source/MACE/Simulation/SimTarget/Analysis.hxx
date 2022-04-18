#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Simulation/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/MPITool/MPIFileTools.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Run.hh"

#include "TFile.h"

namespace MACE::Simulation::SimTarget {

using Core::DataFactory;
using Core::Geometry::Description::Target;
using Utility::ObserverPtr;
using Utility::MPITool::MPIFileTools;

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
    void EnableResultMerge(G4bool val) { fEnableResultMerge = val; }

    void RunBegin(ObserverPtr<const G4Run> run);
    const auto& NewMuoniumTrack() { return fMuoniumTrackList.emplace_back(std::make_unique<MuoniumTrack>()); }
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
    G4bool fEnableResultMerge;

    ObserverPtr<const G4Run> fThisRun;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;

    std::unique_ptr<MPIFileTools> fMPIFileTools;
    std::unique_ptr<TFile> fResultFile;
    std::unique_ptr<std::ofstream> fYieldFile;
    DataFactory fDataFactory;
};

} // namespace MACE::Simulation::SimTarget
