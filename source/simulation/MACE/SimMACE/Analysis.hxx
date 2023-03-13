#pragma once

#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <utility>

class TFile;

namespace MACE::SimMACE {

namespace Hit {

class CDCHit;
class EMCalHit;
class MCPHit;

} // namespace Hit

class Analysis final : public Env::Memory::FreeSingleton<Analysis> {
public:
    Analysis();

    void SetResultPath(const auto& path) { (fResultPath = std::forward<decltype(path)>(path)).replace_extension(); }
    void SetEnableCoincidenceOfEMCal(G4bool val) { fEnableCoincidenceOfEMCal = val; }
    void SetEnableCoincidenceOfMCP(G4bool val) { fEnableCoincidenceOfMCP = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);

    void SubmitEMCalHC(gsl::not_null<const std::vector<gsl::owner<Hit::EMCalHit*>>*> hitList) { fEMCalHitList = hitList; }
    void SubmitMCPHC(gsl::not_null<const std::vector<gsl::owner<Hit::MCPHit*>>*> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(gsl::not_null<const std::vector<gsl::owner<Hit::CDCHit*>>*> hitList) { fCDCHitList = hitList; }
    void WriteEvent(G4int repetitionId);

private:
    void WriteTrees();

private:
    std::unique_ptr<TFile> fFile;

    std::filesystem::path fResultPath;
    G4bool fEnableCoincidenceOfEMCal;
    G4bool fEnableCoincidenceOfMCP;

    DataModel::DataFactory fDataHub;

    G4int fRepetitionIdOfLastG4Event;
    std::shared_ptr<TTree> fEMCalHitTree;
    std::shared_ptr<TTree> fMCPHitTree;
    std::shared_ptr<TTree> fCDCHitTree;

    const std::vector<gsl::owner<Hit::EMCalHit*>>* fEMCalHitList;
    const std::vector<gsl::owner<Hit::MCPHit*>>* fMCPHitList;
    const std::vector<gsl::owner<Hit::CDCHit*>>* fCDCHitList;
};

} // namespace MACE::SimMACE
