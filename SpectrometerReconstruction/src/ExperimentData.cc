#include "TFile.h"
#include "TTreeReader.h"

#include "ExperimentData.hh"

using namespace MACE::SpectrometerReconstruction;

ExperimentData::ExperimentData(const char* rootFile) :
    ExperimentDataBase(0) {

    auto file = new TFile(rootFile, "READ");
    if (!file->IsOpen()) { return; }

    TTreeReader reader("Spectrometer", file);
    TTreeReaderValue<Int_t>   pluseID(reader, "PluseID");
    TTreeReaderValue<Int_t>   trackID(reader, "TrackID");
    TTreeReaderValue<Int_t>   chamberID(reader, "ChamberID");
    TTreeReaderValue<Float_t> vertexTime(reader, "VertexTime");
    TTreeReaderValue<Float_t> vertexPositionX(reader, "VertexPositionX");
    TTreeReaderValue<Float_t> vertexPositionY(reader, "VertexPositionY");
    TTreeReaderValue<Float_t> vertexPositionZ(reader, "VertexPositionZ");
    TTreeReaderValue<Float_t> hitTime(reader, "HitTime");
    TTreeReaderValue<Float_t> hitPositionX(reader, "HitPositionX");
    TTreeReaderValue<Float_t> hitPositionY(reader, "HitPositionY");
    TTreeReaderValue<Float_t> hitPositionZ(reader, "HitPositionZ");

    reader.Next();
    auto thisHitList = &emplace_back(0);
    auto thisPluse = *pluseID;
    do {
        if (thisPluse != *pluseID) {
            thisHitList->shrink_to_fit();
            thisHitList = &emplace_back(0);
            thisHitList->reserve(20);
            thisPluse = *pluseID;
        }
        thisHitList->emplace_back(
            *trackID, *chamberID,
            *vertexTime, TVector3(*vertexPositionX, *vertexPositionY, *vertexPositionZ),
            *hitTime, TVector3(*hitPositionX, *hitPositionY, *hitPositionZ));
    } while (reader.Next());

    file->Close();
    delete file;
}