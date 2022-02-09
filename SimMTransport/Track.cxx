#include "Track.hxx"
#include "SimMTransport/Analysis.hxx"

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
    auto deltaTime = fMonteCarlo->FreePath(fCurrentStep->postPosition) / fCurrentStep->velocity.Mag();
    fCurrentStep->preTime = fCurrentStep->postTime;
    fCurrentStep->postTime += deltaTime;
    fCurrentStep->prePosition = fCurrentStep->postPosition;
    fCurrentStep->postPosition += fCurrentStep->velocity * deltaTime;

    if (!Target(fCurrentStep->postPosition.fX, fCurrentStep->postPosition.fY, fCurrentStep->postPosition.fZ)) {
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
    auto checkDeltaTime = checkStep / fCurrentStep->velocity.Mag();
    auto checkDeltaPosition = fCurrentStep->velocity * checkDeltaTime;
    do {
        if (global->PeriodicBoundaryX() > 0) {
            if (fCurrentStep->postPosition.fX < -global->PeriodicBoundaryX() or fCurrentStep->postPosition.fX > global->PeriodicBoundaryX()) {
                auto denominator = fCurrentStep->postPosition.fX - fCurrentStep->prePosition.fX;
                double_t preRatio;
                TEveVectorD boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.fX > global->PeriodicBoundaryX()) {
                        preRatio = (global->PeriodicBoundaryX() - fCurrentStep->prePosition.fX) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryX() - fCurrentStep->prePosition.fX) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = TEveVectorD(-boundary.fX, boundary.fY, boundary.fZ);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.fX, fCurrentStep->postPosition.fY, fCurrentStep->postPosition.fZ)) {
                    break;
                }
            }
        }
        if (global->PeriodicBoundaryY() > 0) {
            if (fCurrentStep->postPosition.fY < -global->PeriodicBoundaryY() or fCurrentStep->postPosition.fY > global->PeriodicBoundaryY()) {
                auto denominator = fCurrentStep->postPosition.fY - fCurrentStep->prePosition.fY;
                double_t preRatio;
                TEveVectorD boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.fY > global->PeriodicBoundaryY()) {
                        preRatio = (global->PeriodicBoundaryY() - fCurrentStep->prePosition.fY) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryY() - fCurrentStep->prePosition.fY) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = TEveVectorD(boundary.fX, -boundary.fY, boundary.fZ);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.fX, fCurrentStep->postPosition.fY, fCurrentStep->postPosition.fZ)) {
                    break;
                }
            }
        }
        if (global->PeriodicBoundaryZ() > 0) {
            if (fCurrentStep->postPosition.fZ < -global->PeriodicBoundaryZ() or fCurrentStep->postPosition.fZ > global->PeriodicBoundaryZ()) {
                auto denominator = fCurrentStep->postPosition.fZ - fCurrentStep->prePosition.fZ;
                double_t preRatio;
                TEveVectorD boundary;
                if (abs(denominator) < std::numeric_limits<float_t>::epsilon()) {
                    preRatio = 0.5;
                    boundary = 0.5 * (fCurrentStep->postPosition + fCurrentStep->prePosition);
                } else {
                    if (fCurrentStep->postPosition.fZ > global->PeriodicBoundaryZ()) {
                        preRatio = (global->PeriodicBoundaryZ() - fCurrentStep->prePosition.fZ) / denominator;
                    } else {
                        preRatio = (-global->PeriodicBoundaryZ() - fCurrentStep->prePosition.fZ) / denominator;
                    }
                    boundary = fCurrentStep->prePosition + preRatio * (fCurrentStep->postPosition - fCurrentStep->prePosition);
                }
                auto newBoundary = TEveVectorD(boundary.fX, boundary.fY, -boundary.fZ);
                auto newPostTime = fCurrentStep->postTime;
                auto newPostPosition = fCurrentStep->postPosition + newBoundary - boundary;
                fCurrentStep->postTime = fCurrentStep->preTime + preRatio * (fCurrentStep->postTime - fCurrentStep->preTime);
                fCurrentStep->postPosition = boundary;
                if (analysis != nullptr) { analysis->Update(this); }
                fCurrentStep->preTime = fCurrentStep->postTime;
                fCurrentStep->prePosition = newBoundary;
                fCurrentStep->postTime = newPostTime;
                fCurrentStep->postPosition = newPostPosition;
                if (Target(fCurrentStep->postPosition.fX, fCurrentStep->postPosition.fY, fCurrentStep->postPosition.fZ)) {
                    break;
                }
            }
        }
        fCurrentStep->postTime += checkDeltaTime;
        fCurrentStep->postPosition += checkDeltaPosition;
        isNormalStep = false;
        if (fCurrentStep->postTime > fVertexTime + fLife) { return; }
    } while (!Target(fCurrentStep->postPosition.fX, fCurrentStep->postPosition.fY, fCurrentStep->postPosition.fZ));
    fEscaping = false;
    if (isNormalStep) { return; }
    auto out = fCurrentStep->postPosition - checkDeltaPosition;
    auto center = (fCurrentStep->postPosition + out) * 0.5;
    do {
        checkStep *= 0.5;
        checkDeltaTime *= 0.5;
        if (Target(center.fX, center.fY, center.fZ)) {
            fCurrentStep->postTime -= checkDeltaTime;
            fCurrentStep->postPosition = center;
        } else {
            out = center;
        }
        center = (fCurrentStep->postPosition + out) * 0.5;
    } while (checkStep > 0.01 * MeanFreePath(center.fX, center.fY, center.fZ));
}

