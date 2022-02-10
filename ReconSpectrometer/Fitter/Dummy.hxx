#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Fitter.hxx"

template<class SpectromrterHit_t>
class MACE::ReconSpectrometer::Fitter::Dummy final :
    public MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);

    Dummy(const Dummy&) = delete;
    Dummy& operator=(const Dummy&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Fitter<SpectromrterHit_t>;
    using HitPtr = typename Base::HitPtr;

public:
    Dummy();
    ~Dummy();

    bool Fit(const std::vector<HitPtr>& hitData, const HelixParameters& initParameters = defaultHelixParameters) override;

private:
    void SortHitsByCellID();
};

#include "ReconSpectrometer/Fitter/Dummy.txx"