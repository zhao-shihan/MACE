template<template<class H, class T> class FitterT_t, class SpectrometerHit_t, class Track_t>
MACE::ReconTracks::Interface::Tracker<FitterT_t, SpectrometerHit_t, Track_t>::
Tracker() :
    fFitter(std::make_unique<Fitter_t>()),
    fTrackList(0),
    fTrackedHitList(0),
    fOmittedHitList(0) {}
