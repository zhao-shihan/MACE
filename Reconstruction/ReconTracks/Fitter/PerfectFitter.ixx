#include "ReconTracks/Fitter/PerfectFitter.hxx"

template<class SpectrometerHit_t, class Track_t>
bool MACE::ReconTracks::Fitter::PerfectFitter<SpectrometerHit_t, Track_t>::
Fit(std::vector<HitPtr>& hitData, Track_t& track) {
    const auto& firstHit = *std::ranges::min_element(std::as_const(hitData),
        [](const auto& hit1, const auto& hit2) {
            return hit1->GetHitTime() < hit2->GetHitTime();
        }
    );
    track.SetVertexTime(firstHit->GetVertexTime());
    track.SetVertexPosition(firstHit->GetVertexPosition());
    track.SetEnergy(firstHit->GetEnergy());
    track.SetMomentum(firstHit->GetMomentum());
    track.SetCharge((firstHit->GetPDGCode() > 0) ? (-1) : (1));
    track.SetChi2(0);
    return true;
}
