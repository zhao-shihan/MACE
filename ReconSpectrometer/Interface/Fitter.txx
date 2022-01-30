template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t>::
Fitter() :
    fHitData(0),
    fFittedTrack(0),
    fHelixParameter(),
    fUnfittedList(0) {}

template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t>::
~Fitter() {}