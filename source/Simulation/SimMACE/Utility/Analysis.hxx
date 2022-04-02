#pragma once

#include "Core/DataModel/DataFactory.hxx"
#include "Simulation/SimMACE/Hit/CalorimeterHit.hxx"
#include "Simulation/SimMACE/Hit/SpectrometerHit.hxx"
#include "Simulation/SimMACE/Hit/VertexDetectorHit.hxx"
#include "Utility/MPITool/MPIFileTools.hxx"
#include "Utility/ObserverPtr.hxx"

#include "TFile.h"

namespace MACE::Simulation::SimMACE::Utility {

using Core::DataModel::DataFactory;
using Hit::CalorimeterHit;
using Hit::SpectrometerHit;
using Hit::VertexDetectorHit;
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
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetEnableCoincidenceOfVertexDetector(G4bool val) { fEnableCoincidenceOfVertexDetector = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);
    int Merge(G4bool forced = false);

    void SubmitCalorimeterHC(ObserverPtr<const std::vector<CalorimeterHit*>> hitList) { fCalorimeterHitList = hitList; }
    void SubmitVertexDetectorHC(ObserverPtr<const std::vector<VertexDetectorHit*>> hitList) { fVertexDetectorHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<SpectrometerHit*>> hitList) { fSpectrometerHitList = hitList; }
    void WriteEvent(G4int repetitionID);

private:
    void WriteTrees();

private:
    std::unique_ptr<TFile> fFile;
    std::unique_ptr<MPIFileTools> fMPIFileTools;

    G4String fResultName = "untitled_SimMACE";
    G4bool fEnableCoincidenceOfCalorimeter = true;
    G4bool fEnableCoincidenceOfVertexDetector = true;

    DataFactory fDataHub;

    G4int fRepetitionIDOfLastG4Event;
    std::shared_ptr<TTree> fCalorimeterHitTree;
    std::shared_ptr<TTree> fVertexDetectorHitTree;
    std::shared_ptr<TTree> fSpectrometerHitTree;

    ObserverPtr<const std::vector<CalorimeterHit*>> fCalorimeterHitList;
    ObserverPtr<const std::vector<VertexDetectorHit*>> fVertexDetectorHitList;
    ObserverPtr<const std::vector<SpectrometerHit*>> fSpectrometerHitList;
};

} // namespace MACE::Simulation::SimMACE::Utility
