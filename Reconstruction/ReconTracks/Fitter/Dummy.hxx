#pragma once

#include "ReconTracks/Global.hxx"
#include "ReconTracks/Interface/Fitter.hxx"

template<class SpectrometerHit_t, class Track_t>
class MACE::ReconTracks::Fitter::Dummy final :
    public MACE::ReconTracks::Interface::Fitter<SpectrometerHit_t, Track_t> {

    Dummy(const Dummy&) = delete;
    Dummy& operator=(const Dummy&) = delete;

protected:
    using Base = MACE::ReconTracks::Interface::Fitter<SpectrometerHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    Dummy() = default;
    ~Dummy() noexcept = default;

    bool Fit(std::vector<HitPtr>&, Track_t&) override;
};

#include "ReconTracks/Fitter/Dummy.ixx"
