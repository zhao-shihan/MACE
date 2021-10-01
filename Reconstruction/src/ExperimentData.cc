#include "TFile.h"
#include "TTreeReader.h"

#include "ExperimentData.hh"

using namespace MACE::Reconstruction;

ExperimentData::ExperimentData(const char* rootFile) :
    fData(0) {

    auto file = new TFile(rootFile, "READ");
    if (!file->IsOpen()) { return; }

    TTreeReader calorimeterReader("Calorimeter", file);
    TTreeReaderValue<Int_t>       pluseID(calorimeterReader, "PluseID");
    TTreeReaderValue<Int_t>       trackID(calorimeterReader, "TrackID");
    TTreeReaderValue<Float_t>     hitTime(calorimeterReader, "HitTime");
    TTreeReaderValue<Float_t>     energy(calorimeterReader, "Energy");
    TTreeReaderValue<const char*> particleName(calorimeterReader, "ParticleName");

    TTreeReader orbitalDetectorReader("OrbitalDetector", file);
    TTreeReaderValue<Int_t>       pluseID(spectrometerReader, "PluseID");
    TTreeReaderValue<Int_t>       trackID(spectrometerReader, "TrackID");
    TTreeReaderValue<Int_t>       chamberID(spectrometerReader, "ChamberID");
    TTreeReaderValue<Float_t>     vertexTime(spectrometerReader, "VertexTime");
    TTreeReaderValue<Float_t>     vertexPositionX(spectrometerReader, "VertexPositionX");
    TTreeReaderValue<Float_t>     vertexPositionY(spectrometerReader, "VertexPositionY");
    TTreeReaderValue<Float_t>     vertexPositionZ(spectrometerReader, "VertexPositionZ");
    TTreeReaderValue<Float_t>     hitTime(spectrometerReader, "HitTime");
    TTreeReaderValue<Float_t>     hitPositionX(spectrometerReader, "HitPositionX");
    TTreeReaderValue<Float_t>     hitPositionY(spectrometerReader, "HitPositionY");
    TTreeReaderValue<Float_t>     hitPositionZ(spectrometerReader, "HitPositionZ");
    TTreeReaderValue<const char*> particleName(spectrometerReader, "ParticleName");

    TTreeReader spectrometerReader("Spectrometer", file);
    TTreeReaderValue<Int_t>       pluseID(spectrometerReader, "PluseID");
    TTreeReaderValue<Int_t>       trackID(spectrometerReader, "TrackID");
    TTreeReaderValue<Int_t>       chamberID(spectrometerReader, "ChamberID");
    TTreeReaderValue<Float_t>     vertexTime(spectrometerReader, "VertexTime");
    TTreeReaderValue<Float_t>     vertexPositionX(spectrometerReader, "VertexPositionX");
    TTreeReaderValue<Float_t>     vertexPositionY(spectrometerReader, "VertexPositionY");
    TTreeReaderValue<Float_t>     vertexPositionZ(spectrometerReader, "VertexPositionZ");
    TTreeReaderValue<Float_t>     hitTime(spectrometerReader, "HitTime");
    TTreeReaderValue<Float_t>     hitPositionX(spectrometerReader, "HitPositionX");
    TTreeReaderValue<Float_t>     hitPositionY(spectrometerReader, "HitPositionY");
    TTreeReaderValue<Float_t>     hitPositionZ(spectrometerReader, "HitPositionZ");
    TTreeReaderValue<const char*> particleName(spectrometerReader, "ParticleName");

    spectrometerReader.Next();
    auto thisHitList = &emplace_back(0);
    auto thisPluse = *pluseID;
    do {
        if (thisPluse != *pluseID) {
            thisHitList->shrink_to_fit();
            thisHitList = &emplace_back(0);
            thisHitList->reserve(20);
            thisPluse = *pluseID;
        }
        thisHitList->emplace_back();//!!!!!!!!!
    } while (spectrometerReader.Next());

    file->Close();
    delete file;
}