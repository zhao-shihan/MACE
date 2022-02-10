#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/HelixParameters.hxx"

template<template<class T> class FitterT_t, class SpectromrterHit_t>
class MACE::ReconSpectrometer::Interface::Reconstructor {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);
    MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, SpectromrterHit_t);

    Reconstructor(const Reconstructor&) = delete;
    Reconstructor& operator=(const Reconstructor&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectromrterHit_t>;
    using Fitter_t = FitterT_t<SpectromrterHit_t>;

    Reconstructor();
    virtual ~Reconstructor() {}

public:
    virtual void Reconstruct(const std::vector<HitPtr>& hitData) = 0;

    const auto& GetReconstructed() { return fReconstructedList; }
    const auto& GetOmitted() { return fOmittedList; }

protected:
    const std::unique_ptr<Fitter_t> fFitter;

    std::vector<std::pair<HelixParameters, std::vector<HitPtr>>> fReconstructedList;
    std::vector<HitPtr> fOmittedList;
};

#include "ReconSpectrometer/Interface/Reconstructor.txx"
