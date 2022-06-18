#pragma once

#include "MACE/Reconstruction/ReconTracks/Global.hxx"
#include "MACE/Reconstruction/ReconTracks/Interface/Tracker.hxx"

namespace MACE::Reconstruction::ReconTracks::Tracker {

template<template<class H, class T> class FitterT_t, class CDCHit_t, class Track_t>
class PerfectFinder final : public Interface::Tracker<FitterT_t, CDCHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(CDCHit_t);

protected:
    using Base = Interface::Tracker<FitterT_t, CDCHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    PerfectFinder() = default;
    PerfectFinder(const PerfectFinder&) = delete;
    PerfectFinder& operator=(const PerfectFinder&) = delete;
    ~PerfectFinder() noexcept = default;

    void Reconstruct(const std::vector<HitPtr>& hitData) override;

    void SetThreshold(size_t val) { fThreshold = val; }

private:
    static std::vector<HitPtr> LexicographicalSort(std::vector<HitPtr> hitData);
    std::vector<std::vector<HitPtr>> ClassifyToG4Tracks(const std::vector<HitPtr>& sortedHitData) const;
    void CutByLayerID(std::vector<HitPtr>& g4Track);
    void FitAndDumpToResult(std::vector<HitPtr>& candidate);

private:
    size_t fThreshold = 10;
};

} // namespace MACE::Reconstruction::ReconTracks::Tracker

#include "MACE/Reconstruction/ReconTracks/Tracker/PerfectFinder.inl"
