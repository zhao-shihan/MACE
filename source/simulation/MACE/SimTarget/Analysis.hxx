#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <fstream>
#include <memory>

class G4Run;

class TFile;

namespace MACE::SimTarget {

using Core::DataFactory;
using Utility::ObserverPtr;

class Analysis final : private Utility::NonMoveableBase {
public:
    Analysis();
    ~Analysis();

    void SetResultName(std::string_view resultName) { fResultName = resultName; }
    void EnableYieldAnalysis(bool val) { fEnableYieldAnalysis = val; }

    void RunBegin(ObserverPtr<const G4Run> run);
    auto NewMuoniumTrack() { return fMuoniumTrackList.emplace_back(std::make_unique<MuoniumTrack>()).get(); }
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
    std::string fResultName;
    bool fEnableYieldAnalysis;

    ObserverPtr<const G4Run> fThisRun;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;

    std::unique_ptr<TFile> fResultFile;
    std::unique_ptr<std::ofstream> fYieldFile;
    DataFactory fDataFactory;
};

} // namespace MACE::SimTarget
