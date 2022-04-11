#pragma once

#include "MACE/Core/DataFactory.hxx"
// #include "MACE/Simulation/SimTarget
#include "MACE/Utility/MPITool/MPIFileTools.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "TFile.h"

namespace MACE::Simulation::SimTarget {

using Core::DataFactory;
using MACE::Utility::ObserverPtr;
using MACE::Utility::MPITool::MPIFileTools;

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

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);
    int Merge(G4bool forced = false);

    void SubmitEMCalHC(ObserverPtr<const std::vector<EMCalHit*>> hitList) { fEMCalHitList = hitList; }
    void SubmitMCPHC(ObserverPtr<const std::vector<MCPHit*>> hitList) { fMCPHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<CDCHit*>> hitList) { fCDCHitList = hitList; }
    void WriteEvent(G4int repetitionID);

private:
    void WriteTrees();

private:
    G4String fResultName = "SimTarget_result";
    std::unique_ptr<TFile> fFile;
    std::unique_ptr<MPIFileTools> fMPIFileTools;

    DataFactory fDataHub;

    std::shared_ptr<TTree> fEMCalHitTree;
    ObserverPtr<const std::vector<EMCalHit*>> fEMCalHitList;
};

} // namespace MACE::Simulation::SimMACE::Utility
