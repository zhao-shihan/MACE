#pragma once

#include "MACE/ReconTracks/Global.hxx"
#include "MACE/ReconTracks/Interface/Fitter.hxx"

namespace MACE::ReconTracks::Fitter {

template<class CDCHit_t, class Track_t>
class Dummy final : public Interface::Fitter<CDCHit_t, Track_t> {
protected:
    using Base = Interface::Fitter<CDCHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;

public:
    Dummy() = default;
    Dummy(const Dummy&) = delete;
    Dummy& operator=(const Dummy&) = delete;
    ~Dummy() noexcept = default;

    bool Fit(std::vector<HitPtr>&, Track_t&) override;
};

} // namespace MACE::ReconTracks::Fitter

#include "MACE/ReconTracks/Fitter/Dummy.inl"
