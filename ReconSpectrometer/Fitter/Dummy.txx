template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
Dummy() :
    Base() {}

template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
~Dummy() {}

template<class SpectromrterHit_t>
bool MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t>::
Fit(const std::vector<HitPtr>& hitData, const std::optional<HelixParameters>& initParameters) {
    Base::fFittedTrack = hitData;
    Base::fFittedParameters = initParameters.value_or(HelixParameters{ 0.0, 0.0, 0.0, 0.0, 0.0 });
    return true;
}
