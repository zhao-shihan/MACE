#pragma once

#include "Global.hxx"
#include "Step.hxx"
#include "MonteCarlo.hxx"

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
    TEveVectorD fVertexPosition;
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

    [[nodiscard]] const Step* GetCurrentStep() const { return fCurrentStep; }
    [[nodiscard]] double_t GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const TEveVectorD& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] bool IsEscaping() const { return fEscaping; }
    [[nodiscard]] TrackStatus GetTrackStatus() const { return fStatus; }

private:
    bool Target(double_t x, double_t y, double_t z) { return (*global->Target())(x, y, z) > 0.5; }
    double_t MeanFreePath(double_t x, double_t y, double_t z) { return (*global->MeanFreePath())(x, y, z); }
    void EscapingDoIt();
};
