#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Simulation/SimMACE/Hit/CDCHit.hxx"
#include "MACE/Simulation/SimMACE/Hit/EMCalHit.hxx"
#include "MACE/Simulation/SimMACE/Hit/MCPHit.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "TFile.h"

namespace MACE::Simulation::SimMACE::Utility {

using Core::DataFactory;
using Hit::CDCHit;
using Hit::EMCalHit;
using Hit::MCPHit;
using MACE::Utility::ObserverPtr;

class Analysis final {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetResultName(const G4String& resultName) { fResultName = resultName; }
    const G4String& GetResultName() const { return fResultName; }
    void SetEnableCoincidenceOfEMCal(G4bool val) { fEnableCoincidenceOfEMCal = val; }
    void SetEnableCoincidenceOfMCP(G4bool val) { fEnableCoincidenceOfMCP = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);

    void SubmitEMCalHC(ObserverPtr<const std::vector<EMCalHit*>> hitList) { fEMCalHitList = hitList; }
    void SubmitMCPHC(ObserverPtr<const std::vector<MCPHit*>> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<CDCHit*>> hitList) { fCDCHitList = hitList; }
    void WriteEvent(G4int repetitionID);

private:
    void WriteTrees();

private:
    std::unique_ptr<TFile> fFile;

    G4String fResultName = "untitled_SimMACE";
    G4bool fEnableCoincidenceOfEMCal = true;
    G4bool fEnableCoincidenceOfMCP = true;

    DataFactory fDataHub;

    G4int fRepetitionIDOfLastG4Event;
    std::shared_ptr<TTree> fEMCalHitTree;
    std::shared_ptr<TTree> fMCPHitTree;
    std::shared_ptr<TTree> fCDCHitTree;

    ObserverPtr<const std::vector<EMCalHit*>> fEMCalHitList;
    ObserverPtr<const std::vector<MCPHit*>> fMCPHitList;
    ObserverPtr<const std::vector<CDCHit*>> fCDCHitList;
};

} // namespace MACE::Simulation::SimMACE::Utility
