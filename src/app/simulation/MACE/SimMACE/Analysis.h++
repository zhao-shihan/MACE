#pragma once

#include "MACE/Data/Output.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"
#include "MACE/SimMACE/Hit/EMCHit.h++"
#include "MACE/SimMACE/Hit/MCPHit.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::SimMACE {

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileOption(std::string option) -> void { fFileOption = std::move(option); }
    auto CoincidenceWithCDC(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithMCP(bool val) -> void { fCoincidenceWithMCP = val; }
    auto CoincidenceWithEMC(bool val) -> void { fCoincidenceWithEMC = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hitList) -> void { fEMCHitList = &hitList; }
    auto SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hitList) -> void { fMCPHitList = &hitList; }
    auto SubmitSpectrometerHC(const std::vector<gsl::owner<CDCHit*>>& hitList) -> void { fCDCHitList = &hitList; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = nullptr) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileOption;
    bool fCoincidenceWithCDC;
    bool fCoincidenceWithMCP;
    bool fCoincidenceWithEMC;

    gsl::owner<TFile*> fFile;
    std::unique_ptr<Data::Output<Data::CDCSimHit>> fCDCSimHitOutput;
    std::unique_ptr<Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;
    std::unique_ptr<Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;

    const std::vector<gsl::owner<EMCHit*>>* fEMCHitList;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHitList;
    const std::vector<gsl::owner<CDCHit*>>* fCDCHitList;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimMACE
