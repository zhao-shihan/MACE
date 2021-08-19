#ifndef Track_hh
#define Track_hh 1

#include "Global.hh"
#include "Muonium.hh"
#include "MonteCarlo.hh"

namespace MACE {
    namespace SimMuTransport {
        enum TrackStatus {
            kTrackUndefined,
            kTrackInitialized,
            kTrackAlive,
            kTrackDecayed
        };
    }
}

class MACE::SimMuTransport::Track {
private:
    Muonium* const    fMuonium;
    MonteCarlo* const fMonteCarlo;

    double_t              fVertexTime;
    Vector3           fVertexPosition;
    double_t              fLife;

    bool                  fEscaping;

    TrackStatus       fStatus;

public:
    Track();
    ~Track();
    Track(const Track&) = delete;
    Track& operator=(const Track&) = delete;
    bool operator==(const Track& rhs) { return this == &rhs; }

    void Initialize();
    void Stepping();

    const Muonium* GetMuonium() const { return fMuonium; }
    double_t           GetVertexTime() const { return fVertexTime; }
    const Vector3& GetVertexPosition() const { return fVertexPosition; }
    bool               IsEscaping() const { return fEscaping; }
    TrackStatus    GetTrackStatus() const { return fStatus; }

private:
    void EscapingDoIt();
};

#endif

