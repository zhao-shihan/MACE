namespace MACE::ReconTracks::Fitter {

template<class CDCHit_t, class Track_t>
bool Dummy<CDCHit_t, Track_t>::Fit(std::vector<HitPtr>&, Track_t&) {
    return true;
}

} // namespace MACE::ReconTracks::Fitter
