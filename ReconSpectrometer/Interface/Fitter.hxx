#pragma once

#include "ReconSpectrometer/Global.hxx"

template<class SpectromrterHitType> 
class MACE::ReconSpectrometer::Interface::Fitter {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHitType);

    Fitter(const Fitter&) = delete;
    Fitter& operator=(const Fitter&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectromrterHitType>;

    Fitter();
    virtual ~Fitter();

public:
    void SetTrackToBeFitted(const std::vector<HitPtr>& track) { fTrack = std::addressof(track); }
    virtual bool Fit() = 0;
    const auto& GetFittedTrack() const { return fFittedTrack; }
    const auto& GetBadPointList() const { return fBadPointList; }

private:
    const std::vector<HitPtr>* fTrack;
    std::vector<HitPtr> fFittedTrack;
    std::vector<HitPtr> fBadPointList;
};

#include "ReconSpectrometer/Interface/Fitter.txx"