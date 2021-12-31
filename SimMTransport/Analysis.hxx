#pragma once

#include "TFile.h"
#include "TNtuple.h"

#include "Global.hxx"
#include "Track.hxx"

class MACE::SimMTransport::Analysis {
public:
    static Analysis* Instance();
    ~Analysis();
private:
    static Analysis* fInstance;
    Analysis();
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

private:
    size_t fOutputTimeNum;
    double_t* fOutputTime;
    TNtuple** fTimeNtuples;
    TNtuple* fEscapedNtuple;

    bool fOpened;

public:
    void Open();
    void Update(const Track* track) const;
    void WriteAndClose();
};
