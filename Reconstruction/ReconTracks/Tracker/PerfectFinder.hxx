#pragma once

#include "ReconTracks/Global.hxx"
#include "ReconTracks/Interface/Tracker.hxx"

template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
class MACE::ReconTracks::Tracker::PerfectFinder final :
    public MACE::ReconTracks::Interface::Tracker<FitterT_t, SpectromrterHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(SpectromrterHit_t);

    PerfectFinder(const PerfectFinder&) = delete;
    PerfectFinder& operator=(const PerfectFinder&) = delete;

protected:
    using Base = MACE::ReconTracks::Interface::Tracker<FitterT_t, SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    PerfectFinder() = default;
    ~PerfectFinder() noexcept = default;

    void Reconstruct(const std::vector<HitPtr>& hitData) override;

    void SetThreshold(size_t val) { fThreshold = val; }

private:
    static std::vector<HitPtr> LexicographicalSort(std::vector<HitPtr> hitData);
    std::vector<std::vector<HitPtr>> ClassifyToG4Tracks(const std::vector<HitPtr>& sortedHitData) const;
    void CutByLayerID(std::vector<HitPtr>& g4Track);
    void FitAndDumpToResult(std::vector<HitPtr>& candidate);

private:
    size_t fThreshold = 18;
};

#include "ReconTracks/Tracker/PerfectFinder.ixx"
