#include "Analysis.hxx"
#include "Track.hxx"

#include <sstream>

using MACE::Simulation::SimMTransport::Analysis;

Analysis* Analysis::fInstance = nullptr;

Analysis* Analysis::Instance() {
    if (fInstance == nullptr) {
        if (Global::Instance()->CommRank() != Global::Instance()->MasterRank()) {
            fInstance = new Analysis();
        }
    }
    return fInstance;
}

Analysis::Analysis() :
    fOutputTimeNum(0),
    fOutputTime(nullptr),
    fTimeNtuples(nullptr),
    fEscapedNtuple(nullptr),
    fOpened(false) {}

void Analysis::Open() {
    if (fOpened) { return; }

    new TFile(TString(Global::Instance()->Name()) + "_rank" + Global::Instance()->CommRank() + ".root", "RECREATE");

    fOutputTimeNum = 1;
    for (double time = Global::Instance()->BeginTime(); time < Global::Instance()->EndTime(); time += Global::Instance()->OutputStep()) {
        ++fOutputTimeNum;
    }

    fOutputTime = new double[fOutputTimeNum];
    for (size_t timeId = 0; timeId < fOutputTimeNum - 1; ++timeId) {
        fOutputTime[timeId] = Global::Instance()->BeginTime() + timeId * Global::Instance()->OutputStep();
    }
    fOutputTime[fOutputTimeNum - 1] = Global::Instance()->EndTime();

    fTimeNtuples = new TNtuple*[fOutputTimeNum];
    for (size_t timeId = 0; timeId < fOutputTimeNum; ++timeId) {
        std::stringstream ss;
        TString NtupleName;
        ss << "t=" << fOutputTime[timeId] << "us";
        ss >> NtupleName;
        fTimeNtuples[timeId] = new TNtuple(
            NtupleName,
            NtupleName,
            "x:y:z");
    }

    fEscapedNtuple = new TNtuple(
        "Escaped",
        "Escaped",
        "x_vertex:y_vertex:z_vertex:t_vertex:x_decay:y_decay:z_decay:t_decay");

    fOpened = true;
}

void Analysis::Update(const Track* track) const {
    if (!fOpened) { return; }

    for (size_t timeId = 0; timeId < fOutputTimeNum; ++timeId) {
        if (track->GetCurrentStep()->preTime <= fOutputTime[timeId] and
            track->GetCurrentStep()->postTime > fOutputTime[timeId]) {
            auto interPosition = track->GetCurrentStep()->prePosition + ((fOutputTime[timeId] - track->GetCurrentStep()->preTime) / (track->GetCurrentStep()->postTime - track->GetCurrentStep()->preTime)) * (track->GetCurrentStep()->postPosition - track->GetCurrentStep()->prePosition);
            fTimeNtuples[timeId]->Fill(
                interPosition.fX,
                interPosition.fY,
                interPosition.fZ);
            break;
        }
    }
    if (track->GetTrackStatus() == kTrackDecayed and track->IsEscaping()) {
        fEscapedNtuple->Fill(
            track->GetVertexPosition().fX,
            track->GetVertexPosition().fY,
            track->GetVertexPosition().fZ,
            track->GetVertexTime(),
            track->GetCurrentStep()->postPosition.fX,
            track->GetCurrentStep()->postPosition.fY,
            track->GetCurrentStep()->postPosition.fZ,
            track->GetCurrentStep()->postTime);
    }
}

void Analysis::WriteAndClose() {
    if (!fOpened) { return; }

    gFile->Write();
    gFile->Close();

    delete[] fOutputTime;
    delete[] fTimeNtuples;

    fOpened = false;
}
