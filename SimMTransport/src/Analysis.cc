#include <sstream>

#include "Analysis.hh"

using namespace MACE::SimMTransport;

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

Analysis::~Analysis() {}

void Analysis::Open() {
    if (fOpened) { return; }

    new TFile(TString(Global::Instance()->Name()) + "_rank" + Global::Instance()->CommRank() + ".root", "RECREATE");

    fOutputTimeNum = 1;
    for (double_t time = Global::Instance()->BeginTime(); time < Global::Instance()->EndTime(); time += Global::Instance()->OutputStep()) {
        ++fOutputTimeNum;
    }

    fOutputTime = new double_t[fOutputTimeNum];
    for (size_t timeId = 0; timeId < fOutputTimeNum - 1; ++timeId) {
        fOutputTime[timeId] = Global::Instance()->BeginTime() + timeId * Global::Instance()->OutputStep();
    }
    fOutputTime[fOutputTimeNum - 1] = Global::Instance()->EndTime();

    fTimeNtuples = new TNtuple * [fOutputTimeNum];
    for (size_t timeId = 0; timeId < fOutputTimeNum; ++timeId) {
        std::stringstream ss;
        TString NtupleName;
        ss << "t=" << fOutputTime[timeId] << "us";
        ss >> NtupleName;
        fTimeNtuples[timeId] = new TNtuple(
            NtupleName,
            NtupleName,
            "x:y:z"
        );
    }

    fEscapedNtuple = new TNtuple(
        "Escaped",
        "Escaped",
        "x_vertex:y_vertex:z_vertex:t_vertex:x_decay:y_decay:z_decay:t_decay"
    );

    fOpened = true;
}

void Analysis::Update(const Track* track) const {
    if (!fOpened) { return; }

    for (size_t timeId = 0; timeId < fOutputTimeNum; ++timeId) {
        if (track->GetCurrentStep()->preTime <= fOutputTime[timeId] &&
            track->GetCurrentStep()->postTime > fOutputTime[timeId]) {
            auto interPosition = track->GetCurrentStep()->prePosition + ((fOutputTime[timeId] - track->GetCurrentStep()->preTime) / (track->GetCurrentStep()->postTime - track->GetCurrentStep()->preTime)) * (track->GetCurrentStep()->postPosition - track->GetCurrentStep()->prePosition);
            fTimeNtuples[timeId]->Fill(
                interPosition.x,
                interPosition.y,
                interPosition.z
            );
            break;
        }
    }
    if (track->GetTrackStatus() == kTrackDecayed && track->IsEscaping()) {
        fEscapedNtuple->Fill(
            track->GetVertexPosition().x,
            track->GetVertexPosition().y,
            track->GetVertexPosition().z,
            track->GetVertexTime(),
            track->GetCurrentStep()->postPosition.x,
            track->GetCurrentStep()->postPosition.y,
            track->GetCurrentStep()->postPosition.z,
            track->GetCurrentStep()->postTime
        );
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

