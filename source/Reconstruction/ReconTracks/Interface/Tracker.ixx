namespace MACE::Reconstruction::ReconTracks::Interface {

template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
Tracker<FitterT_t, SpectrometerHit_t, Track_t>::
    Tracker() :
    fFitter(std::make_unique<Fitter_t>()),
    fTrackList(0),
    fTrackedHitList(0),
    fOmittedHitList(0) {}

} // namespace MACE::Reconstruction::ReconTracks::Interface
