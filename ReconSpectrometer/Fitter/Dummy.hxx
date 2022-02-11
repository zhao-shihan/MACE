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
    Dummy();
    ~Dummy();

    bool Fit(const std::vector<HitPtr>& hitData, const Track_t& seed) override;

private:
    void SortHitsByCellID();
};

#include "ReconSpectrometer/Fitter/Dummy.txx"
