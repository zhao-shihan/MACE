#pragma once

#include "MACE/Data/Output.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Hit/EMCHit.h++"
#include "MACE/SimEMC/Hit/MCPHit.h++"
#include "MACE/SimEMC/Hit/PMTHit.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::SimEMC {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileOption(std::string option) -> void { fFileOption = std::move(option); }
    auto EnableCoincidenceOfEMC(G4bool val) -> void { fEnableCoincidenceOfEMC = val; }
    auto EnableCoincidenceOfMCP(G4bool val) -> void { fEnableCoincidenceOfMCP = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hitList) -> void { fEMCHitList = &hitList; }
    auto SubmitPMTHC(const std::vector<gsl::owner<PMTHit*>>& hitList) -> void { fPMTHitList = &hitList; }
    auto SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hitList) -> void { fMCPHitList = &hitList; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = nullptr) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileOption;
    G4bool fEnableCoincidenceOfEMC;
    G4bool fEnableCoincidenceOfMCP;

    gsl::owner<TFile*> fFile;
    std::unique_ptr<Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;
    std::unique_ptr<Data::Output<Data::PMTSimHit>> fPMTSimHitOutput;
    std::unique_ptr<Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;

    const std::vector<gsl::owner<EMCHit*>>* fEMCHitList;
    const std::vector<gsl::owner<PMTHit*>>* fPMTHitList;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHitList;
};

} // namespace MACE::SimEMC
