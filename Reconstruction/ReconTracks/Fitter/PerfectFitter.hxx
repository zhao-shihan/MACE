#pragma once

#include "Utility/LiteralUnit.hxx"
#include "Reconstruction/ReconTracks/Interface/Fitter.hxx"

namespace MACE::Reconstruction::ReconTracks::Fitter {

template<class SpectrometerHit_t, class Track_t>
class PerfectFitter final : public Interface::Fitter<SpectrometerHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(SpectrometerHit_t);
    MACE_RECONSPECTROMETER_PHYSICSTRACK_CONCEPT(Track_t);

protected:
    using Base = Interface::Fitter<SpectrometerHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    PerfectFitter() = default;
    PerfectFitter(const PerfectFitter&) = delete;
    PerfectFitter& operator=(const PerfectFitter&) = delete;
    ~PerfectFitter() noexcept = default;

    bool Fit(std::vector<HitPtr>& hitData, Track_t& track) override;
};

} // namespace MACE::Reconstruction::ReconTracks::Fitter

#include "Reconstruction/ReconTracks/Fitter/PerfectFitter.ixx"
