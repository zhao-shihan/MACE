#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHitType>
class MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHitType> {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHitType);

    DirectLeastChiSquare(const DirectLeastChiSquare&) = delete;
    DirectLeastChiSquare& operator=(const DirectLeastChiSquare&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHitType>;
    using HitPtr = std::shared_ptr<SpectromrterHitType>;

public:
    DirectLeastChiSquare();
    ~DirectLeastChiSquare();

    bool Fit() override { return true; }
};

#include "ReconSpectrometer/Fitter/DirectLeastChiSquare.txx"