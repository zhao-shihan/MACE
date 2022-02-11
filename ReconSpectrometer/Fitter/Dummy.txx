template<class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t, Track_t>::
Dummy() :
    Base() {}

template<class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t, Track_t>::
~Dummy() {}

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t, Track_t>::
Fit(const std::vector<HitPtr>& hitData, const Track_t& seed) {
    Base::fFittedList = hitData;
    Base::fFittedTrack = std::make_shared<Track_t>(seed);
    return true;
}
