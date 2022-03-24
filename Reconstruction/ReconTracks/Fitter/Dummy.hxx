#pragma once

#include "ReconTracks/Global.hxx"
#include "ReconTracks/Interface/Fitter.hxx"

namespace MACE::Reconstruction::ReconTracks::Fitter {

template<class SpectrometerHit_t, class Track_t>
class Dummy final : public Interface::Fitter<SpectrometerHit_t, Track_t> {
protected:
    using Base = Interface::Fitter<SpectrometerHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    Dummy() = default;
    Dummy(const Dummy&) = delete;
    Dummy& operator=(const Dummy&) = delete;
    ~Dummy() noexcept = default;

    bool Fit(std::vector<HitPtr>&, Track_t&) override;
};

} // namespace MACE::Reconstruction::ReconTracks::Fitter

#include "ReconTracks/Fitter/Dummy.ixx"
