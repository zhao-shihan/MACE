#pragma once

#include "MACE/ReconTracks/Interface/Fitter.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::ReconTracks::Fitter {

template<class CDCHit_t, class Track_t>
class PerfectFitter final : public Interface::Fitter<CDCHit_t, Track_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(CDCHit_t);
    MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t);

protected:
    using Base = Interface::Fitter<CDCHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    PerfectFitter() = default;
    PerfectFitter(const PerfectFitter&) = delete;
    PerfectFitter& operator=(const PerfectFitter&) = delete;
    ~PerfectFitter() noexcept = default;

    bool Fit(std::vector<HitPtr>& hitData, Track_t& track) override;
};

} // namespace MACE::ReconTracks::Fitter

#include "MACE/ReconTracks/Fitter/PerfectFitter.inl"
