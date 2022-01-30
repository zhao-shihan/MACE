#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHit_t>
class MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);

    DirectLeastChiSquare(const DirectLeastChiSquare&) = delete;
    DirectLeastChiSquare& operator=(const DirectLeastChiSquare&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t>;
    using HitPtr = typename Base::HitPtr;

public:
    DirectLeastChiSquare();
    ~DirectLeastChiSquare();

    bool Fit() override;

private:
    void SortHitsByCellID();
};

#include "ReconSpectrometer/Fitter/DirectLeastChiSquare.txx"