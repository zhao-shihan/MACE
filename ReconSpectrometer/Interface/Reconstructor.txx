template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t>::
Reconstructor() :
    fFitter(std::make_unique<Fitter_t>()),
    fReconstructedList(0),
    fOmittedList(0) {}

template<template<class T> class FitterT_t, class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t>::
~Reconstructor() {}
