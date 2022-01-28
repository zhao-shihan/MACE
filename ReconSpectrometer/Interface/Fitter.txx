template<class SpectromrterHitType>
MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHitType>::
Fitter() :
    fTrack(nullptr),
    fFittedTrack(0),
    fBadPointList(0) {}

template<class SpectromrterHitType>
MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHitType>::
~Fitter() {}