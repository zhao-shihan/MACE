#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "TFormula.h"

#include <fstream>
#include <memory>

class G4Run;

class TFile;

namespace MACE::SimTarget {

using Core::DataFactory;
using Utility::ObserverPtr;

class Analysis final : public Environment::Resource::Singleton<Analysis> {
    friend class Environment::Resource::SingletonFactory;

private:
    Analysis();
    ~Analysis() = default;

public:
    void SetResultName(std::string_view resultName) { fResultName = resultName; }
    void EnableYieldAnalysis(bool val) { fEnableYieldAnalysis = val; }
    void SetDetectableRegion(const char* booleanExpression) { fDetectableRegion = ConstructFormula(booleanExpression); }

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

    static TFormula ConstructFormula(const char* booleanExpression) { return TFormula("DetectableRegion", booleanExpression, false); }
    bool IsDetectable(const Double_t* pos) const noexcept { return fDetectableRegion.EvalPar(pos); }

private:
    std::string fResultName;
    bool fEnableYieldAnalysis;
    TFormula fDetectableRegion;

    ObserverPtr<const G4Run> fThisRun;
    std::vector<std::unique_ptr<MuoniumTrack>> fMuoniumTrackList;

    std::unique_ptr<TFile> fResultFile;
    std::unique_ptr<std::ofstream> fYieldFile;
    DataFactory fDataFactory;
};

} // namespace MACE::SimTarget
