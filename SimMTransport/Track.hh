#pragma once

#include "Global.hh"
#include "Step.hh"
#include "MonteCarlo.hh"

namespace MACE {
    namespace SimMTransport {
        enum TrackStatus {
            kTrackUndefined,
            kTrackInitialized,
            kTrackAlive,
            kTrackDecayed
        };
    }
}

class MACE::SimMTransport::Track {
protected:
    Step* const       fCurrentStep;
    MonteCarlo* const fMonteCarlo;

    double_t          fVertexTime;
    CLHEP::Hep3Vector fVertexPosition;
    double_t          fLife;

    bool              fEscaping;

    TrackStatus       fStatus;

    Global* global;
    Analysis* analysis;

public:
    Track();
    ~Track();
    Track(const Track&) = delete;
    Track& operator=(const Track&) = delete;
    bool operator==(const Track& rhs) { return this == &rhs; }

    void Initialize();
    void Stepping();

    const Step* GetCurrentStep() const { return fCurrentStep; }
    double_t GetVertexTime() const { return fVertexTime; }
    const CLHEP::Hep3Vector& GetVertexPosition() const { return fVertexPosition; }
    bool IsEscaping() const { return fEscaping; }
    TrackStatus GetTrackStatus() const { return fStatus; }

private:
    bool Target(double_t x, double_t y, double_t z) { return (*global->Target())(x, y, z) > 0.5; }
    double_t MeanFreePath(double_t x, double_t y, double_t z) { return (*global->MeanFreePath())(x, y, z); }
    void EscapingDoIt();
};
