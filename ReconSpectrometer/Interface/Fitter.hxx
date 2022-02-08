#pragma once

#include <optional>

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
    virtual bool Fit(const std::vector<HitPtr>& hitData, const std::optional<HelixParameters>& initParameters) = 0;

    const auto& GetFittedParameters() const { return fFittedParameters; }
    const auto& GetFittedTrack() const { return fFittedTrack; }
    const auto& GetOmittedList() const { return fOmittedList; }

protected:
    HelixParameters     fFittedParameters;
    std::vector<HitPtr> fFittedTrack;
    std::vector<HitPtr> fOmittedList;
};

#include "ReconSpectrometer/Interface/Fitter.txx"