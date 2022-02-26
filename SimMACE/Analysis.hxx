#pragma once

#include "TFile.h"

#include "SimMACE/Global.hxx"
#include "SimMACE/Hit/CalorimeterHit.hxx"
#include "SimMACE/Hit/VertexDetectorHit.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "DataModel/DataHub.hxx"
#include "Utility/ObserverPtr.hxx"
#include "Utility/FileTools4MPI.hxx"

class MACE::SimMACE::Analysis final {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetResultName(const G4String& resultName) { fResultName = resultName; }
    [[nodiscard]] const G4String& GetResultName() const { return fResultName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetEnableCoincidenceOfVertexDetector(G4bool val) { fEnableCoincidenceOfVertexDetector = val; }

    void Open(Option_t* option = "recreate");
    void Close(Option_t* option = nullptr);
    int Merge(G4bool forced = false);

    void SubmitCalorimeterHC(ObserverPtr<const std::vector<Hit::CalorimeterHit*>> hitList) { fCalorimeterHitList = hitList; }
    void SubmitVertexDetectorHC(ObserverPtr<const std::vector<Hit::VertexDetectorHit*>> hitList) { fVertexDetectorHitList = hitList; }
    void SubmitSpectrometerHC(ObserverPtr<const std::vector<Hit::SpectrometerHit*>> hitList) { fSpectrometerHitList = hitList; }
    void WriteEvent(G4int repetitionID);

private:
    void WriteTrees();

private:
    std::unique_ptr<TFile>         fFile;
    std::unique_ptr<FileTools4MPI> fFileTools4MPI;

    G4String fResultName = "untitled_SimMACE";
    G4bool   fEnableCoincidenceOfCalorimeter = true;
    G4bool   fEnableCoincidenceOfVertexDetector = true;

    DataModel::DataHub fDataHub;

    G4int fRepetitionIDOfLastG4Event;
    std::shared_ptr<TTree> fCalorimeterHitTree;
    std::shared_ptr<TTree> fVertexDetectorHitTree;
    std::shared_ptr<TTree> fSpectrometerHitTree;

    ObserverPtr<const std::vector<Hit::CalorimeterHit*>> fCalorimeterHitList;
    ObserverPtr<const std::vector<Hit::VertexDetectorHit*>> fVertexDetectorHitList;
    ObserverPtr<const std::vector<Hit::SpectrometerHit*>> fSpectrometerHitList;
};
