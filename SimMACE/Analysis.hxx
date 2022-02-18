#pragma once

#include "TFile.h"

#include "SimMACE/Global.hxx"
#include "SimMACE/Hit/CalorimeterHit.hxx"
#include "SimMACE/Hit/VertexDetectorHit.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "DataModel/DataHub.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Analysis final {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetFileName(const G4String& fileName) { fFileName = fileName; }
    [[nodiscard]] const G4String& GetFileName() const { return fFileName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetEnableCoincidenceOfVertexDetector(G4bool val) { fEnableCoincidenceOfVertexDetector = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);

    void SetTrueEventID(G4int trueEventID) { fTrueEventID = trueEventID; }
    void SubmitCalorimeterHC(ObserverPtr<const std::vector<Hit::CalorimeterHit*>> hitList) { fCalorimeterHitList = hitList; }
    void SubmitVertexDetectorHC(ObserverPtr<const std::vector<Hit::VertexDetectorHit*>> hitList) { fVertexDetectorHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<Hit::SpectrometerHit*>> hitList) { fSpectrometerHitList = hitList; }
    void WriteEvent();

private:
    std::unique_ptr<TFile> fFile;
    DataModel::DataHub fDataHub;

    G4String fFileName = "untitled_SimMACE";
    G4bool   fEnableCoincidenceOfCalorimeter = true;
    G4bool   fEnableCoincidenceOfVertexDetector = true;
    G4int    fTrueEventID;

    ObserverPtr<const std::vector<Hit::CalorimeterHit*>> fCalorimeterHitList;
    ObserverPtr<const std::vector<Hit::VertexDetectorHit*>> fVertexDetectorHitList;
    ObserverPtr<const std::vector<Hit::SpectrometerHit*>> fSpectrometerHitList;
};
