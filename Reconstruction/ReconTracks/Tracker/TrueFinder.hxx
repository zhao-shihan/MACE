#pragma once

#include "ReconTracks/Global.hxx"
#include "ReconTracks/Interface/Tracker.hxx"

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
class MACE::ReconTracks::Tracker::TrueFinder final :
    public MACE::ReconTracks::Interface::Tracker<FitterT_t, SpectromrterHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(SpectromrterHit_t);

    TrueFinder(const TrueFinder&) = delete;
    TrueFinder& operator=(const TrueFinder&) = delete;

protected:
    using Base = MACE::ReconTracks::Interface::Tracker<FitterT_t, SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    TrueFinder() = default;
    ~TrueFinder() noexcept = default;

    void Reconstruct(const std::vector<HitPtr>& hitData) override;

    void SetThreshold(size_t val) { fThreshold = val; }

private:
    std::vector<std::vector<HitPtr>> Classify(const std::vector<HitPtr>& hitData);

private:
    size_t fThreshold = 18;
};

#include "ReconTracks/Tracker/TrueFinder.ixx"
