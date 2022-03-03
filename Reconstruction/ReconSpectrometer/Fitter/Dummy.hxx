#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHit_t, class Track_t>
class MACE::ReconSpectrometer::Fitter::Dummy final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t> {

    Dummy(const Dummy&) = delete;
    Dummy& operator=(const Dummy&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    Dummy() = default;
    ~Dummy() noexcept = default;

    bool Fit(std::vector<HitPtr>& hitData, TrackPtr& seed) override;
};

#include "ReconSpectrometer/Fitter/Dummy.ixx"
