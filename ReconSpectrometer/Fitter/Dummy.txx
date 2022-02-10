template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
Dummy() :
    Base() {}

template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
~Dummy() {}

template<class SpectromrterHit_t>
bool MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
Fit(const std::vector<HitPtr>& hitData, const HelixParameters& initParameters) {
    Base::fFittedTrack = hitData;
    Base::fFittedParameters = initParameters;
    return true;
}
