template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t>::
Reconstructor() :
    fHitData(0),
    fFitter(std::make_unique<Fitter_t>()),
    fReconstructedTrackList(0) {}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t>::
~Reconstructor() {}
