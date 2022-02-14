#pragma once

#include "SimMACE/Global.hxx"
#include "SimMACE/Hit/CalorimeterHit.hxx"
#include "SimMACE/Hit/VertexDetectorHit.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"

#include "DataModel/PersistencyWriter.hxx"

class MACE::SimMACE::Analysis final :
    private MACE::DataModel::PersistencyWriter {
public:
    static Analysis& Instance();

private:
    Analysis();
    ~Analysis() noexcept = default;
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void SetFileName(const G4String& fileName) { fFileName = fileName; }
    const G4String& GetFileName() const { return fFileName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetEnableCoincidenceOfVertexDetector(G4bool val) { fEnableCoincidenceOfVertexDetector = val; }

    void Open();
    using DataModel::PersistencyWriter::Close;

    void SetTrueEventID(G4int trueEventID) { fTrueEventID = trueEventID; }
    void SubmitCalorimeterHC(const std::vector<Hit::CalorimeterHit*>* hitList) { fpCalorimeterHitList = hitList; }
    void SubmitVertexDetectorHC(const std::vector<Hit::VertexDetectorHit*>* hitList) { fpVertexDetectorHitList = hitList; }
    void SubmitSpectrometerHC(const std::vector<Hit::SpectrometerHit*>* hitList) { fpSpectrometerHitList = hitList; }
    void WriteEvent();

private:
    G4String fFileName = "untitled_SimMACE";
    G4bool   fEnableCoincidenceOfCalorimeter = true;
    G4bool   fEnableCoincidenceOfVertexDetector = true;
    G4int    fTrueEventID;

    const std::vector<Hit::CalorimeterHit*>* fpCalorimeterHitList;
    const std::vector<Hit::VertexDetectorHit*>* fpVertexDetectorHitList;
    const std::vector<Hit::SpectrometerHit*>* fpSpectrometerHitList;
};