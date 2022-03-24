#pragma once

#include "Global.hxx"

#include "TFile.h"
#include "TNtuple.h"

namespace MACE::Simulation::SimMTransport {

class Track;

class Analysis {
public:
    static Analysis* Instance();
    ~Analysis() noexcept = default;

private:
    static Analysis* fInstance;
    Analysis();
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

private:
    size_t fOutputTimeNum;
    double* fOutputTime;
    TNtuple** fTimeNtuples;
    TNtuple* fEscapedNtuple;

    bool fOpened;

public:
    void Open();
    void Update(const Track* track) const;
    void WriteAndClose();
};

} // namespace MACE::Simulation::SimMTransport
