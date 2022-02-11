template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t, Track_t>::
Reconstructor() :
    fFitter(std::make_unique<Fitter_t>()),
    fTrackList(0),
    fReconstructedHitList(0),
    fOmittedHitList(0) {}
