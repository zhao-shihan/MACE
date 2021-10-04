#include "hit/transient/Calorimeter.hh"
#include "hit/persistency/Calorimeter.hh"

using namespace MACE::DataModel::Hit;

Transient::Calorimeter::Calorimeter() :
    fParticleName(nullptr),
    fHitTime(0.0),
    fEnergy(0.0),
    fTrackID(-1) {}

Transient::Calorimeter::Calorimeter(const Calorimeter& hit) :
    fParticleName(hit.fParticleName),
    fHitTime(hit.fHitTime),
    fEnergy(hit.fEnergy),
    fTrackID(hit.fTrackID) {}

Transient::Calorimeter::Calorimeter(Calorimeter&& hit) :
    fParticleName(std::move(hit.fParticleName)),
    fHitTime(std::move(hit.fHitTime)),
    fEnergy(std::move(hit.fEnergy)),
    fTrackID(std::move(hit.fTrackID)) {}

Transient::Calorimeter& Transient::Calorimeter::operator=(const Calorimeter& hit) {
    fParticleName = hit.fParticleName;
    fHitTime = hit.fHitTime;
    fEnergy = hit.fEnergy;
    fTrackID = hit.fTrackID;
    return *this;
}

Transient::Calorimeter& Transient::Calorimeter::operator=(Calorimeter&& hit) {
    fParticleName = std::move(hit.fParticleName);
    fHitTime = std::move(hit.fHitTime);
    fEnergy = std::move(hit.fEnergy);
    fTrackID = std::move(hit.fTrackID);
    return *this;
}

Transient::Calorimeter::Calorimeter(const Persistency::Calorimeter& hit) :
    fParticleName(hit.ParticleName),
    fHitTime(hit.HitTime),
    fEnergy(hit.Energy),
    fTrackID(hit.TrackID) {}

Transient::Calorimeter::Calorimeter(Persistency::Calorimeter&& hit) :
    fParticleName(std::move(hit.ParticleName)),
    fHitTime(std::move(hit.HitTime)),
    fEnergy(std::move(hit.Energy)),
    fTrackID(std::move(hit.TrackID)) {}

Transient::Calorimeter& Transient::Calorimeter::operator=(const Persistency::Calorimeter& hit) {
    fParticleName = hit.ParticleName;
    fHitTime = hit.HitTime;
    fEnergy = hit.Energy;
    fTrackID = hit.TrackID;
    return *this;
}

Transient::Calorimeter& Transient::Calorimeter::operator=(Persistency::Calorimeter&& hit) {
    fParticleName = std::move(hit.ParticleName);
    fHitTime = std::move(hit.HitTime);
    fEnergy = std::move(hit.Energy);
    fTrackID = std::move(hit.TrackID);
    return *this;
}

Persistency::Calorimeter Transient::Calorimeter::ToPersistency() {
    return Persistency::Calorimeter{
        (const char*)fParticleName,
        (float)fHitTime,
        (float)fEnergy,
        (int)fTrackID
    };
}
