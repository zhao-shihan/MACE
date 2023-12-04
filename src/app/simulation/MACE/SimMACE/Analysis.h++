#pragma once

#include "MACE/Data/Output.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
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

    void FilePath(std::filesystem::path path) { fFilePath = std::move(path); }
    void FileOption(std::string option) { fFileOption = std::move(option); }
    void CoincidenceWithCDC(bool val) { fCoincidenceWithMCP = val; }
    void CoincidenceWithMCP(bool val) { fCoincidenceWithMCP = val; }
    void CoincidenceWithEMC(bool val) { fCoincidenceWithEMC = val; }

    void RunBegin(G4int runID);

    void SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hitList) { fEMCHitList = &hitList; }
    void SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hitList) { fMCPHitList = &hitList; }
    void SubmitSpectrometerHC(const std::vector<gsl::owner<CDCHit*>>& hitList) { fCDCHitList = &hitList; }
    void EventEnd();

    void RunEnd(Option_t* option = nullptr);

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
};

} // namespace MACE::SimMACE
