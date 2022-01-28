#pragma once

#include "ReconSpectrometer/Global.hxx"

template<template<class T> class FitterType, class SpectromrterHitType>
class MACE::ReconSpectrometer::Interface::Reconstructor {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHitType);
    MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterType, SpectromrterHitType);

    Reconstructor(const Reconstructor&) = delete;
    Reconstructor& operator=(const Reconstructor&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectromrterHitType>;

    Reconstructor();
    virtual ~Reconstructor();

public:
    void SetHitDataToBeRecongnized(const std::vector<HitPtr>& hitData) { fHitData = hitData; }
    virtual void Reconstruct() = 0;
    const auto& GetRecognizedTrackList() { return fReconstructedTrackList; }

protected:
    FitterType<SpectromrterHitType>& Fitter() const { return *fFitter; }

protected:
    std::vector<HitPtr> fHitData;
    std::vector<std::vector<HitPtr>> fReconstructedTrackList;

private:
    FitterType<SpectromrterHitType>* fFitter;
};

#include "ReconSpectrometer/Interface/Reconstructor.txx"
