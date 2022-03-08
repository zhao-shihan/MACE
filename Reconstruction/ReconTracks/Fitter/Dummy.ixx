template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconTracks::Fitter::Dummy<SpectromrterHit_t, Track_t>::
Fit(std::vector<HitPtr>&, Track_t&) {
    return true;
}
