namespace MACE::ReconTracks::Fitter {

template<class CDCHit_t, class Track_t>
bool PerfectFitter<CDCHit_t, Track_t>::Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    using namespace DataModel::Track;

    const auto& firstHit = *std::ranges::min_element(
        std::as_const(hitData),
        [](const auto& hit1, const auto& hit2) {
            return hit1->HitTime() < hit2->HitTime();
        });

    if constexpr (std::same_as<Track_t, CDCPhysicsTrack>) {
        track.VertexTime(firstHit->VertexTime());
        track.VertexPosition(firstHit->VertexPosition());
        track.VertexEnergy(firstHit->VertexEnergy());
        track.VertexMomentum(firstHit->VertexMomentum());
        track.Particle(firstHit->Particle());
        track.SetNumHits(hitData.size());
        track.SetChi2(0);
    } else {
        CDCPhysicsTrack physTrack;
        physTrack.VertexTime(firstHit->VertexTime());
        physTrack.VertexPosition(firstHit->VertexPosition());
        physTrack.VertexEnergy(firstHit->VertexEnergy());
        physTrack.VertexMomentum(firstHit->VertexMomentum());
        physTrack.Particle(firstHit->Particle());
        physTrack.SetNumHits(hitData.size());
        physTrack.SetChi2(0);
        track = Track_t(physTrack);
    }
    return true;
}

} // namespace MACE::ReconTracks::Fitter
