template<class SpectrometerHit_t, class Track_t>
bool MACE::ReconTracks::Fitter::Dummy<SpectrometerHit_t, Track_t>::
Fit(std::vector<HitPtr>&, Track_t&) {
    return true;
}
