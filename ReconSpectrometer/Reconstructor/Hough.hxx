#pragma once

#include "Eigen/Core"

#include "ReconSpectrometer/Global.hxx"
#include "ReconSpectrometer/Interface/Reconstructor.hxx"

template<template<class T> class FitterType, class SpectromrterHitType>
class MACE::ReconSpectrometer::Reconstructor::Hough final :
    public MACE::ReconSpectrometer::Interface::Reconstructor<FitterType, SpectromrterHitType> {

    Hough(const Hough&) = delete;
    Hough& operator=(const Hough&) = delete;

protected:
    using Base = MACE::ReconSpectrometer::Interface::Reconstructor<FitterType, SpectromrterHitType>;
    using HitPtr = typename Base::HitPtr;

public:
    Hough(double r0Low, double r0Up, Eigen::Index nPhi, Eigen::Index nRho, double z0Low, double z0Up, Eigen::Index nZ0, Eigen::Index nAlpha);
    ~Hough();

    void Reconstruct() override;
    const auto& GetRecognizedParameterList() const { return fRecognizedParameterList; }

    void SetThresholdXY(size_t threshold) { fThresholdXY = threshold; }
    void SetThresholdSZ(size_t threshold) { fThresholdSZ = threshold; }

private:
    // Step 1
    void HoughTransformXY();
    void FindExceedThresholdXY();
    // Step 2
    // Loop over fPiledTrackList
    //     SubStep 1
    void HoughTransformSZ(const std::vector<HitPtr*>* piledTracks, const std::pair<double, double>& center);
    void FindExceedThresholdSZ(const std::pair<double, double>& center);
    //     SubStep 2
    void DumpToResult();
    // End loop

    double ToPhiReal(Eigen::Index i) const { return -M_PI + (i + 0.5) * fPhiResolution; }
    double ToRhoReal(Eigen::Index j) const { return fRhoLow + (j + 0.5) * fRhoResolution; }
    Eigen::Index ToPhiIndex(double phi) const { return (phi + M_PI) / fPhiResolution; }
    Eigen::Index ToRhoIndex(double rho) const { return (rho - fRhoLow) / fRhoResolution; }

    double ToZ0Real(Eigen::Index j) const { return fZ0Low + (j + 0.5) * fZ0Resolution; }
    double ToAlphaReal(Eigen::Index i) const { return -M_PI + (i + 0.5) * fAlphaResolution; }
    Eigen::Index ToZ0Index(double z0) const { return (z0 - fZ0Low) / fZ0Resolution; }
    Eigen::Index ToAlphaIndex(double alpha) const { return (alpha + M_PI) / fAlphaResolution; }

    static size_t EffectiveSizeOf(const std::vector<HitPtr*>& hitPtrList) { return std::count_if(hitPtrList.begin(), hitPtrList.end(), [](auto hitPtr) { return (bool)(*hitPtr); }); }

private:
    const double fRhoLow;
    const double fRhoUp;
    const double fPhiResolution;
    const double fRhoResolution;
    size_t fThresholdXY = 20;
    Eigen::Matrix<std::vector<HitPtr*>, Eigen::Dynamic, Eigen::Dynamic> fHoughSpaceXY;
    std::vector<std::pair<const std::vector<HitPtr*>*, std::pair<double, double>>> fPiledTrackList;

    const double fZ0Low;
    const double fZ0Up;
    const double fZ0Resolution;
    const double fAlphaResolution;
    size_t fThresholdSZ = 20;
    Eigen::Matrix<std::vector<HitPtr*>, Eigen::Dynamic, Eigen::Dynamic> fHoughSpaceSZ;
    std::vector<std::pair<const std::vector<HitPtr*>*, std::tuple<double, double, double, double>>> fTrackList;

    std::vector<std::tuple<double, double, double, double>> fRecognizedParameterList;
};

#include "ReconSpectrometer/Reconstructor/Hough.txx"