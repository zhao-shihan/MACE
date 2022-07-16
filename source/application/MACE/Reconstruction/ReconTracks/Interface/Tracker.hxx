#pragma once

#include "MACE/Reconstruction/ReconTracks/Global.hxx"

namespace MACE::Reconstruction::ReconTracks::Interface {

template<template<class H, class T> class FitterT_t, class CDCHit_t, class Track_t>
class Tracker {
    MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, CDCHit_t, Track_t);
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(CDCHit_t);
    MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t);

protected:
    using Fitter_t = FitterT_t<CDCHit_t, Track_t>;
    using HitPtr = std::shared_ptr<CDCHit_t>;
    using TrackPtr = std::shared_ptr<Track_t>;

    Tracker();
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;
    virtual ~Tracker() noexcept = default;

public:
    const auto& GetFitter() const { return fFitter; }

    virtual void Reconstruct(const std::vector<HitPtr>& hitData) = 0;

    const auto& GetTrackList() const { return fTrackList; }
    const auto& GetTrackedHitList() const { return fTrackedHitList; }
    const auto& GetOmittedHitList() const { return fOmittedHitList; }

protected:
    const std::unique_ptr<Fitter_t> fFitter;

    std::vector<TrackPtr> fTrackList;
    std::vector<std::vector<HitPtr>> fTrackedHitList;
    std::vector<HitPtr> fOmittedHitList;
};

} // namespace MACE::Reconstruction::ReconTracks::Interface

#include "MACE/Reconstruction/ReconTracks/Interface/Tracker.inl"
