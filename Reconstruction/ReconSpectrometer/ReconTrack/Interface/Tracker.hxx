#pragma once

#include "ReconSpectrometer/ReconTrack/Global.hxx"

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
class MACE::ReconSpectrometer::Interface::Tracker {
    MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, SpectromrterHit_t, Track_t);
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);
    MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t);

    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;

protected:
    using Fitter_t = FitterT_t<SpectromrterHit_t, Track_t>;
    using HitPtr = std::shared_ptr<SpectromrterHit_t>;
    using TrackPtr = std::shared_ptr<Track_t>;

    Tracker();
    virtual ~Tracker() noexcept = default;

public:
    [[nodiscard]] const auto& GetFitter() const { return fFitter; }

    virtual void Reconstruct(const std::vector<HitPtr>& hitData) = 0;

    [[nodiscard]] const auto& GetTrackList() const { return fTrackList; }
    [[nodiscard]] const auto& GetReconstructedHitList() const { return fReconstructedHitList; }
    [[nodiscard]] const auto& GetOmittedHitList() const { return fOmittedHitList; }

protected:
    const std::unique_ptr<Fitter_t> fFitter;

    std::vector<TrackPtr> fTrackList;
    std::vector<std::vector<HitPtr>> fReconstructedHitList;
    std::vector<HitPtr> fOmittedHitList;
};

#include "ReconSpectrometer/ReconTrack/Interface/Tracker.ixx"
