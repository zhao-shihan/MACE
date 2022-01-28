template<template<class T> class FitterType, class SpectromrterHitType>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterType, SpectromrterHitType>::
Reconstructor() :
    fHitData(0),
    fReconstructedTrackList(0),
    fFitter(new FitterType<SpectromrterHitType>()) {}

template<template<class T> class FitterType, class SpectromrterHitType>
MACE::ReconSpectrometer::Interface::Reconstructor<FitterType, SpectromrterHitType>::
~Reconstructor() {
    delete fFitter;
}
