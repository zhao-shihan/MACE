#pragma once

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Reconstructor.hxx"

template<template<class T> class FitterT_t, class SpectromrterHit_t>
class MACE::ReconSpectrometer::Reconstructor::TrueFinder final :
    public MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t> {
    MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(SpectromrterHit_t);

    TrueFinder(const TrueFinder&) = delete;
    TrueFinder& operator=(const TrueFinder&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Reconstructor<FitterT_t, SpectromrterHit_t>;
    using HitPtr = typename Base::HitPtr;

public:
    TrueFinder();
    ~TrueFinder() {}

    void Reconstruct(const std::vector<HitPtr>& hitData) override;

    void SetThreshold(size_t val) { fThreshold = val; }

private:
    size_t fThreshold = 10;

    std::vector<std::vector<HitPtr>> fClassifier;
};

#include "ReconSpectrometer/Reconstructor/TrueFinder.txx"
