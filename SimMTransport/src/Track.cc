#include "Track.hh"
#include "Analysis.hh"

using namespace MACE::SimMTransport;

Track::Track() :
    fCurrentStep(new Step()),
    fMonteCarlo(new MonteCarlo()),
    fVertexTime(0.),
    fVertexPosition(),
    fLife(0.),
    fEscaping(false),
    fStatus(kTrackUndefined),
    global(Global::Instance()),
    analysis(nullptr) {}

Track::~Track() {
    delete fCurrentStep;
    delete fMonteCarlo;
}

void Track::Initialize() {
    fVertexTime = fMonteCarlo->VertexTime();
    fVertexPosition = fMonteCarlo->VertexPosition();
    fLife = fMonteCarlo->Life();

    fCurrentStep->postTime = fVertexTime;
    fCurrentStep->postPosition = fVertexPosition;

    fEscaping = false;

    if (analysis == nullptr) { analysis = Analysis::Instance(); }

    fStatus = kTrackInitialized;
}

void Track::Stepping() {
    if (fStatus == kTrackInitialized) { fStatus = kTrackAlive; }
    if (fStatus != kTrackAlive) { return; }

    fCurrentStep->velocity = fMonteCarlo->MaxwellBoltzmann();
    auto deltaTime = fMonteCarlo->FreePath(fCurrentStep->postPosition) / fCurrentStep->velocity.Norm();
    fCurrentStep->preTime = fCurrentStep->postTime;
    fCurrentStep->postTime += deltaTime;
    fCurrentStep->prePosition = fCurrentStep->postPosition;
    fCurrentStep->postPosition += fCurrentStep->velocity * deltaTime;

    if (!Target(fCurrentStep->postPosition.x, fCurrentStep->postPosition.y, fCurrentStep->postPosition.z)) {
        EscapingDoIt();
    }

    if (fCurrentStep->postTime > fVertexTime + fLife) {
        fStatus = kTrackDecayed;
    }

    if (analysis != nullptr) { analysis->Update(this); }
}

void Track::EscapingDoIt() {
    fEscaping = true;
    bool isNormalStep = true;
    auto checkStep = global->StepOfPushing();
    auto checkDeltaTime = checkStep / fCurrentStep->velocity.Norm();
    auto checkDeltaPosition = fCurrentStep->velocity * checkDeltaTime;
    do {
        if (global->PeriodicBoundaryX() > 0) {
            if (fCurrentStep->postPosition.x < -global->PeriodicBoundaryX() || fCurrentStep->postPosition.x > global->PeriodicBoundaryX()) {
                auto denominator = fCurrentStep->postPosition.x - fCurrentStep->prePosition.x;
                double_t preRatio;
                Vector3 boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.x > global->PeriodicBoundaryX()) {
                        preRatio = (global->PeriodicBoundaryX() - fCurrentStep->prePosition.x) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryX() - fCurrentStep->prePosition.x) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = Vector3(-boundary.x, boundary.y, boundary.z);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.x, fCurrentStep->postPosition.y, fCurrentStep->postPosition.z)) {
                    break;
                }
            }
        }
        if (global->PeriodicBoundaryY() > 0) {
            if (fCurrentStep->postPosition.y < -global->PeriodicBoundaryY() || fCurrentStep->postPosition.y > global->PeriodicBoundaryY()) {
                auto denominator = fCurrentStep->postPosition.y - fCurrentStep->prePosition.y;
                double_t preRatio;
                Vector3 boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.y > global->PeriodicBoundaryY()) {
                        preRatio = (global->PeriodicBoundaryY() - fCurrentStep->prePosition.y) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryY() - fCurrentStep->prePosition.y) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = Vector3(boundary.x, -boundary.y, boundary.z);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.x, fCurrentStep->postPosition.y, fCurrentStep->postPosition.z)) {
                    break;
                }
            }
        }
        if (global->PeriodicBoundaryZ() > 0) {
            if (fCurrentStep->postPosition.z < -global->PeriodicBoundaryZ() || fCurrentStep->postPosition.z > global->PeriodicBoundaryZ()) {
                auto denominator = fCurrentStep->postPosition.z - fCurrentStep->prePosition.z;
                double_t preRatio;
                Vector3 boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.z > global->PeriodicBoundaryZ()) {
                        preRatio = (global->PeriodicBoundaryZ() - fCurrentStep->prePosition.z) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryZ() - fCurrentStep->prePosition.z) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = Vector3(boundary.x, boundary.y, -boundary.z);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.x, fCurrentStep->postPosition.y, fCurrentStep->postPosition.z)) {
                    break;
                }
            }
        }
        fCurrentStep->postTime += checkDeltaTime;
        fCurrentStep->postPosition += checkDeltaPosition;
        isNormalStep = false;
        if (fCurrentStep->postTime > fVertexTime + fLife) { return; }
    } while (!Target(fCurrentStep->postPosition.x, fCurrentStep->postPosition.y, fCurrentStep->postPosition.z));
    fEscaping = false;
    if (isNormalStep) { return; }
    auto out = fCurrentStep->postPosition - checkDeltaPosition;
    auto center = (fCurrentStep->postPosition + out) * 0.5;
    do {
        checkStep *= 0.5;
        checkDeltaTime *= 0.5;
        if (Target(center.x, center.y, center.z)) {
            fCurrentStep->postTime -= checkDeltaTime;
            fCurrentStep->postPosition = center;
        } else {
            out = center;
        }
        center = (fCurrentStep->postPosition + out) * 0.5;
    } while (checkStep > 0.01 * MeanFreePath(center.x, center.y, center.z));
}

