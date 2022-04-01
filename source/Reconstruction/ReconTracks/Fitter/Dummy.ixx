namespace MACE::Reconstruction::ReconTracks::Fitter {

template<class SpectrometerHit_t, class Track_t>
bool Dummy<SpectrometerHit_t, Track_t>::Fit(std::vector<HitPtr>&, Track_t&) {
    return true;
}

} // namespace MACE::Reconstruction::ReconTracks::Fitter
