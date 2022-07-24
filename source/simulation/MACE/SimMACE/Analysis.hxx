#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4String.hh"
#include "G4Types.hh"

class TFile;

namespace MACE::SimMACE {

namespace Hit {

class CDCHit;
class EMCalHit;
class MCPHit;

} // namespace Hit

using Core::DataFactory;
using MACE::Utility::ObserverPtr;

class Analysis final : public Environment::Memory::Singleton<Analysis> {
    friend Environment::Memory::SingletonFactory;

private:
    Analysis();
    ~Analysis() = default;

public:
    void SetResultName(const G4String& resultName) { fResultName = resultName; }
    const G4String& GetResultName() const { return fResultName; }
    void SetEnableCoincidenceOfEMCal(G4bool val) { fEnableCoincidenceOfEMCal = val; }
    void SetEnableCoincidenceOfMCP(G4bool val) { fEnableCoincidenceOfMCP = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);

    void SubmitEMCalHC(ObserverPtr<const std::vector<Hit::EMCalHit*>> hitList) { fEMCalHitList = hitList; }
    void SubmitMCPHC(ObserverPtr<const std::vector<Hit::MCPHit*>> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<Hit::CDCHit*>> hitList) { fCDCHitList = hitList; }
    void WriteEvent(G4int repetitionID);

private:
    void WriteTrees();

private:
    std::unique_ptr<TFile> fFile;

    G4String fResultName;
    G4bool fEnableCoincidenceOfEMCal;
    G4bool fEnableCoincidenceOfMCP;

    DataFactory fDataHub;

    G4int fRepetitionIDOfLastG4Event;
    std::shared_ptr<TTree> fEMCalHitTree;
    std::shared_ptr<TTree> fMCPHitTree;
    std::shared_ptr<TTree> fCDCHitTree;

    ObserverPtr<const std::vector<Hit::EMCalHit*>> fEMCalHitList;
    ObserverPtr<const std::vector<Hit::MCPHit*>> fMCPHitList;
    ObserverPtr<const std::vector<Hit::CDCHit*>> fCDCHitList;
};

} // namespace MACE::SimMACE
