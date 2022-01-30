#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/HelixParameters.hxx"

template<class SpectromrterHit_t>
class MACE::ReconSpectrometer::Interface::Fitter {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);

    Fitter(const Fitter&) = delete;
    Fitter& operator=(const Fitter&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectromrterHit_t>;

    Fitter();
    virtual ~Fitter();

public:
    void SetHitDataToBeFitted(const std::vector<HitPtr>& hitData) { fHitData = hitData; }
    virtual bool Fit() = 0;
    const auto& GetFittedTrack() const { return fFittedTrack; }
    const auto& GetHelixParameter() const { return fHelixParameter; }
    const auto& GetUnfittedList() const { return fUnfittedList; }

protected:
    std::vector<HitPtr> fHitData;
    std::vector<HitPtr> fFittedTrack;
    HelixParameters     fHelixParameter;
    std::vector<HitPtr> fUnfittedList;
};

#include "ReconSpectrometer/Interface/Fitter.txx"