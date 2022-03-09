#pragma once

#include "ReconTracks/Interface/Fitter.hxx"
#include "LiteralUnits.hxx"

template<class SpectrometerHit_t, class Track_t>
class MACE::ReconTracks::Fitter::PerfectFitter final :
    public MACE::ReconTracks::Interface::Fitter<SpectrometerHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(SpectrometerHit_t);
    MACE_RECONSPECTROMETER_PHYSICSTRACK_CONCEPT(Track_t);
protected:
    using Base = MACE::ReconTracks::Interface::Fitter<SpectrometerHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    PerfectFitter() = default;
    ~PerfectFitter() noexcept = default;
    PerfectFitter(const PerfectFitter&) = delete;
    PerfectFitter& operator=(const PerfectFitter&) = delete;

    bool Fit(std::vector<HitPtr>& hitData, Track_t& track) override;
};

#include "ReconTracks/Fitter/PerfectFitter.ixx"
