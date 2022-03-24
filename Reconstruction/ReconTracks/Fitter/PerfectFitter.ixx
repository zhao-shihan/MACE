namespace MACE::Reconstruction::ReconTracks::Fitter {

template<class SpectrometerHit_t, class Track_t>
bool PerfectFitter<SpectrometerHit_t, Track_t>::Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    const auto& firstHit = *std::ranges::min_element(
        std::as_const(hitData),
        [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        });
    track.SetVertexTime(firstHit->GetVertexTime());
    track.SetVertexPosition(firstHit->GetVertexPosition());
    track.SetVertexEnergy(firstHit->GetVertexEnergy());
    track.SetVertexMomentum(firstHit->GetVertexMomentum());
    track.SetParticleName(firstHit->GetParticleName());
    track.SetNumberOfFittedPoints(hitData.size());
    track.SetChi2(0);
    return true;
}

} // namespace MACE::Reconstruction::ReconTracks::Fitter
