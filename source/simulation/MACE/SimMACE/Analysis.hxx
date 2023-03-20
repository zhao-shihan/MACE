#pragma once

#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/Env/Memory/PassiveSingleton.hxx"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <utility>

class TFile;

namespace MACE::SimMACE {

inline namespace Hit {

class CDCHit;
class EMCalHit;
class MCPHit;

} // inline namespace Hit

class Analysis final : public Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    void ResultPath(const auto& path) { (fResultPath = std::forward<decltype(path)>(path)).replace_extension(); }
    void EnableCoincidenceOfEMCal(G4bool val) { fEnableCoincidenceOfEMCal = val; }
    void EnableCoincidenceOfMCP(G4bool val) { fEnableCoincidenceOfMCP = val; }

    void RunBegin(G4int runID, Option_t* option = "recreate");

    void SubmitEMCalHC(gsl::not_null<const std::vector<gsl::owner<EMCalHit*>>*> hitList) { fEMCalHitList = hitList; }
    void SubmitMCPHC(gsl::not_null<const std::vector<gsl::owner<MCPHit*>>*> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(gsl::not_null<const std::vector<gsl::owner<CDCHit*>>*> hitList) { fCDCHitList = hitList; }
    void EventEnd();

    void RunEnd(Option_t* option = nullptr);

private:
    std::filesystem::path fResultPath;
    G4bool fEnableCoincidenceOfEMCal;
    G4bool fEnableCoincidenceOfMCP;

    DataModel::DataFactory fDataHub;
    std::unique_ptr<TFile> fFile;
    std::shared_ptr<TTree> fEMCalHitTree;
    std::shared_ptr<TTree> fMCPHitTree;
    std::shared_ptr<TTree> fCDCHitTree;

    const std::vector<gsl::owner<EMCalHit*>>* fEMCalHitList;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHitList;
    const std::vector<gsl::owner<CDCHit*>>* fCDCHitList;
};

} // namespace MACE::SimMACE
