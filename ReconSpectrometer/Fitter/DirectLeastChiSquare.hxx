#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHit_t, class Track_t>
class MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t> {
    MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t);

    DirectLeastChiSquare(const DirectLeastChiSquare&) = delete;
    DirectLeastChiSquare& operator=(const DirectLeastChiSquare&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t, Track_t>;
    using HitPtr = typename Base::HitPtr;
    using TrackPtr = typename Base::TrackPtr;

public:
    DirectLeastChiSquare();
    ~DirectLeastChiSquare();

    bool Fit(const std::vector<HitPtr>& hitData, const Track_t& seed) override;

private:
    void SortHitsByCellID();
};

#include "ReconSpectrometer/Fitter/DirectLeastChiSquare.txx"