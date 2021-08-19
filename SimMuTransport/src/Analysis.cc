#include <sstream>

#include "Analysis.hh"

using namespace MACE::SimMuTransport;

Analysis* Analysis::fInstance = nullptr;

Analysis* Analysis::Instance() {
    if (fInstance == nullptr) {
        if (gCommRank != gMasterRank) {
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

    new TFile(TString(gName) + "_rank" + gCommRank + ".root", "RECREATE");

    fOutputTimeNum = 1;
    for (double_t time = gBeginTime; time < gEndTime; time += gOutputStep) {
        ++fOutputTimeNum;
    }

    fOutputTime = new double_t[fOutputTimeNum];
    for (size_t timeId = 0; timeId < fOutputTimeNum - 1; ++timeId) {
        fOutputTime[timeId] = gBeginTime + timeId * gOutputStep;
    }
    fOutputTime[fOutputTimeNum - 1] = gEndTime;

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
        if (track->GetMuonium()->preTime <= fOutputTime[timeId] &&
            track->GetMuonium()->postTime > fOutputTime[timeId]) {
            auto interPosition = track->GetMuonium()->prePosition + ((fOutputTime[timeId] - track->GetMuonium()->preTime) / (track->GetMuonium()->postTime - track->GetMuonium()->preTime)) * (track->GetMuonium()->postPosition - track->GetMuonium()->prePosition);
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
            track->GetMuonium()->postPosition.x,
            track->GetMuonium()->postPosition.y,
            track->GetMuonium()->postPosition.z,
            track->GetMuonium()->postTime
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

