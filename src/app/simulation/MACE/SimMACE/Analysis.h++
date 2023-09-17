#pragma once

#include "MACE/DataModel/DataFactory.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::SimMACE {

inline namespace Hit {

class CDCHit;
class EMCHit;
class MCPHit;

} // inline namespace Hit

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    void FilePath(std::filesystem::path path) { fFilePath = std::move(path); }
    void FileOption(std::string option) { fFileOption = std::move(option); }
    void EnableCoincidenceOfEMC(G4bool val) { fEnableCoincidenceOfEMC = val; }
    void EnableCoincidenceOfMCP(G4bool val) { fEnableCoincidenceOfMCP = val; }

    void RunBegin(G4int runID);

    void SubmitEMCHC(gsl::not_null<const std::vector<gsl::owner<EMCHit*>>*> hitList) { fEMCHitList = hitList; }
    void SubmitMCPHC(gsl::not_null<const std::vector<gsl::owner<MCPHit*>>*> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(gsl::not_null<const std::vector<gsl::owner<CDCHit*>>*> hitList) { fCDCHitList = hitList; }
    void EventEnd();

    void RunEnd(Option_t* option = nullptr);

private:
    std::filesystem::path fFilePath;
    std::string fFileOption;
    G4bool fEnableCoincidenceOfEMC;
    G4bool fEnableCoincidenceOfMCP;

    DataModel::DataFactory fDataHub;
    std::unique_ptr<TFile> fFile;
    std::shared_ptr<TTree> fEMCHitTree;
    std::shared_ptr<TTree> fMCPHitTree;
    std::shared_ptr<TTree> fCDCHitTree;

    const std::vector<gsl::owner<EMCHit*>>* fEMCHitList;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHitList;
    const std::vector<gsl::owner<CDCHit*>>* fCDCHitList;
};

} // namespace MACE::SimMACE
