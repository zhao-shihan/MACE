#include "Track.hh"
#include "Analysis.hh"

using namespace MACE::SimMuTransport;

Track::Track() :
    fMuonium(new Muonium()),
    fMonteCarlo(new MonteCarlo()),
    fVertexTime(0.),
    fVertexPosition(),
    fLife(0.),
    fEscaping(false),
    fStatus(kTrackUndefined) {}

Track::~Track() {
    delete fMuonium;
    delete fMonteCarlo;
}

static Analysis* analysis = nullptr;

void Track::Initialize() {
    fVertexTime = fMonteCarlo->VertexTime();
    fVertexPosition = fMonteCarlo->VertexPosition();
    fLife = fMonteCarlo->Life();

    fMuonium->postTime = fVertexTime;
    fMuonium->postPosition = fVertexPosition;

    fEscaping = false;

    if (analysis == nullptr) { analysis = Analysis::Instance(); }

    fStatus = kTrackInitialized;
}

void Track::Stepping() {
    if (fStatus == kTrackInitialized) { fStatus = kTrackAlive; }
    if (fStatus != kTrackAlive) { return; }

    fMuonium->velocity = fMonteCarlo->MaxwellBoltzmann();
    auto deltaTime = fMonteCarlo->FreePath(fMuonium->postPosition) / fMuonium->velocity.Norm();
    fMuonium->preTime = fMuonium->postTime;
    fMuonium->postTime += deltaTime;
    fMuonium->prePosition = fMuonium->postPosition;
    fMuonium->postPosition += fMuonium->velocity * deltaTime;

    if (!gTarget(fMuonium->postPosition.x, fMuonium->postPosition.y, fMuonium->postPosition.z)) {
        EscapingDoIt();
    }

    if (fMuonium->postTime > fVertexTime + fLife) {
        fStatus = kTrackDecayed;
    }

    analysis->Update(this);
}

void Track::EscapingDoIt() {
    fEscaping = true;
    bool isNormalStep = true;
    auto checkStep = gStepOfPushing;
    auto checkDeltaTime = checkStep / fMuonium->velocity.Norm();
    auto checkDeltaPosition = fMuonium->velocity * checkDeltaTime;
    do {
#ifdef PERIODIC_BOUNDARY_X
        if (fMuonium->postPosition.x < -gPeriodicBoundaryX || fMuonium->postPosition.x > gPeriodicBoundaryX) {
            auto denominator = fMuonium->postPosition.x - fMuonium->prePosition.x;
            double_t preRatio;
            Vector3 boundary;
            if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                preRatio = 0.5;
                boundary = 0.5 * (fMuonium->postPosition + fMuonium->prePosition);
            } else {
                if (fMuonium->postPosition.x > gPeriodicBoundaryX) {
                    preRatio = (gPeriodicBoundaryX - fMuonium->prePosition.x) / denominator;
                } else {
                    preRatio = (-gPeriodicBoundaryX - fMuonium->prePosition.x) / denominator;
                }
                boundary = fMuonium->prePosition + preRatio * (fMuonium->postPosition - fMuonium->prePosition);
            }
            auto newBoundary = Vector3(-boundary.x, boundary.y, boundary.z);
            auto newPostTime = fMuonium->postTime;
            auto newPostPosition = fMuonium->postPosition + newBoundary - boundary;
            fMuonium->postTime = fMuonium->preTime + preRatio * (fMuonium->postTime - fMuonium->preTime);
            fMuonium->postPosition = boundary;
            analysis->Update(this);
            fMuonium->preTime = fMuonium->postTime;
            fMuonium->prePosition = newBoundary;
            fMuonium->postTime = newPostTime;
            fMuonium->postPosition = newPostPosition;
            if (gTarget(fMuonium->postPosition.x, fMuonium->postPosition.y, fMuonium->postPosition.z)) {
                break;
            }
        }
#endif
#ifdef PERIODIC_BOUNDARY_Y
        if (fMuonium->postPosition.y < -gPeriodicBoundaryY || fMuonium->postPosition.y > gPeriodicBoundaryY) {
            auto denominator = fMuonium->postPosition.y - fMuonium->prePosition.y;
            double_t preRatio;
            Vector3 boundary;
            if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                preRatio = 0.5;
                boundary = 0.5 * (fMuonium->postPosition + fMuonium->prePosition);
            } else {
                if (fMuonium->postPosition.y > gPeriodicBoundaryY) {
                    preRatio = (gPeriodicBoundaryY - fMuonium->prePosition.y) / denominator;
                } else {
                    preRatio = (-gPeriodicBoundaryY - fMuonium->prePosition.y) / denominator;
                }
                boundary = fMuonium->prePosition + preRatio * (fMuonium->postPosition - fMuonium->prePosition);
            }
            auto newBoundary = Vector3(boundary.x, -boundary.y, boundary.z);
            auto newPostTime = fMuonium->postTime;
            auto newPostPosition = fMuonium->postPosition + newBoundary - boundary;
            fMuonium->postTime = fMuonium->preTime + preRatio * (fMuonium->postTime - fMuonium->preTime);
            fMuonium->postPosition = boundary;
            analysis->Update(this);
            fMuonium->preTime = fMuonium->postTime;
            fMuonium->prePosition = newBoundary;
            fMuonium->postTime = newPostTime;
            fMuonium->postPosition = newPostPosition;
            if (gTarget(fMuonium->postPosition.x, fMuonium->postPosition.y, fMuonium->postPosition.z)) {
                break;
            }
        }
#endif
#ifdef PERIODIC_BOUNDARY_Z
        if (fMuonium->postPosition.z < -gPeriodicBoundaryZ || fMuonium->postPosition.z > gPeriodicBoundaryZ) {
            auto denominator = fMuonium->postPosition.z - fMuonium->prePosition.z;
            double_t preRatio;
            Vector3 boundary;
            if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                preRatio = 0.5;
                boundary = 0.5 * (fMuonium->postPosition + fMuonium->prePosition);
            } else {
                if (fMuonium->postPosition.z > gPeriodicBoundaryZ) {
                    preRatio = (gPeriodicBoundaryZ - fMuonium->prePosition.z) / denominator;
                } else {
                    preRatio = (-gPeriodicBoundaryZ - fMuonium->prePosition.z) / denominator;
                }
                boundary = fMuonium->prePosition + preRatio * (fMuonium->postPosition - fMuonium->prePosition);
            }
            auto newBoundary = Vector3(boundary.x, boundary.y, -boundary.z);
            auto newPostTime = fMuonium->postTime;
            auto newPostPosition = fMuonium->postPosition + newBoundary - boundary;
            fMuonium->postTime = fMuonium->preTime + preRatio * (fMuonium->postTime - fMuonium->preTime);
            fMuonium->postPosition = boundary;
            analysis->Update(this);
            fMuonium->preTime = fMuonium->postTime;
            fMuonium->prePosition = newBoundary;
            fMuonium->postTime = newPostTime;
            fMuonium->postPosition = newPostPosition;
            if (gTarget(fMuonium->postPosition.x, fMuonium->postPosition.y, fMuonium->postPosition.z)) {
                break;
            }
        }
#endif
        fMuonium->postTime += checkDeltaTime;
        fMuonium->postPosition += checkDeltaPosition;
        isNormalStep = false;
        if (fMuonium->postTime > fVertexTime + fLife) { return; }
    } while (!gTarget(fMuonium->postPosition.x, fMuonium->postPosition.y, fMuonium->postPosition.z));
    fEscaping = false;
    if (isNormalStep) { return; }
    auto out = fMuonium->postPosition - checkDeltaPosition;
    auto center = (fMuonium->postPosition + out) * 0.5;
    do {
        checkStep *= 0.5;
        checkDeltaTime *= 0.5;
        if (gTarget(center.x, center.y, center.z)) {
            fMuonium->postTime -= checkDeltaTime;
            fMuonium->postPosition = center;
        } else {
            out = center;
        }
        center = (fMuonium->postPosition + out) * 0.5;
    } while (checkStep > 0.01 * gMeanFreePath(center.x, center.y, center.z));
}

