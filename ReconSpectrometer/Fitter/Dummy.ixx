template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::Dummy<SpectromrterHit_t, Track_t>::
Fit(std::vector<HitPtr>& hitData, TrackPtr& seed) {
    return true;
}
