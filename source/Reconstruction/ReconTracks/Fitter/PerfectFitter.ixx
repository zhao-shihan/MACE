namespace MACE::Reconstruction::ReconTracks::Fitter {

template<class SpectrometerHit_t, class Track_t>
bool PerfectFitter<SpectrometerHit_t, Track_t>::Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    using namespace Core::DataModel::Track;

    const auto& firstHit = *std::ranges::min_element(
        std::as_const(hitData),
        [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        });

    if constexpr (std::same_as<Track_t, CDCPhysicsTrack>) {
        track.SetVertexTime(firstHit->GetVertexTime());
        track.SetVertexPosition(firstHit->GetVertexPosition());
        track.SetVertexEnergy(firstHit->GetVertexEnergy());
        track.SetVertexMomentum(firstHit->GetVertexMomentum());
        track.SetParticle(firstHit->GetParticle());
        track.SetNumHits(hitData.size());
        track.SetChi2(0);
    } else {
        CDCPhysicsTrack physTrack;
        physTrack.SetVertexTime(firstHit->GetVertexTime());
        physTrack.SetVertexPosition(firstHit->GetVertexPosition());
        physTrack.SetVertexEnergy(firstHit->GetVertexEnergy());
        physTrack.SetVertexMomentum(firstHit->GetVertexMomentum());
        physTrack.SetParticle(firstHit->GetParticle());
        physTrack.SetNumHits(hitData.size());
        physTrack.SetChi2(0);
        track = Track_t(physTrack);
    }
    return true;
}

} // namespace MACE::Reconstruction::ReconTracks::Fitter
