/* #pragma once

#include "MACE/ReconTracks/Global.hxx"
#include "MACE/ReconTracks/Interface/Tracker.hxx"

#include "Eigen/Core"

template<template<class T> class FitterT_t, class CDCHit_t>
class MACE::ReconTracks::Tracker::Hough final :
    public MACE::ReconTracks::Interface::Tracker<FitterT_t, CDCHit_t> {

    Hough(const Hough&) = delete;
    Hough& operator=(const Hough&) = delete;

protected:
    using Base = MACE::ReconTracks::Interface::Tracker<FitterT_t, CDCHit_t>;
    using HitPtr = typename Base::HitPtr;

public:
    Hough(double r0Low, double r0Up, Eigen::Index nPhi, Eigen::Index nRho, double z0Low, double z0Up, Eigen::Index nZ0, Eigen::Index nAlpha);
    ~Hough() noexcept;

    void Reconstruct(const std::vector<HitPtr>& hitData) override;

    void SetThresholdXY(size_t threshold) { fThresholdXY = threshold; }
    void SetThresholdSZ(size_t threshold) { fThresholdSZ = threshold; }

private:
    // Step 1: 2D pattern recognition
    void HoughTransformXY();
    void FindExceedThresholdXY();
    // Step 2
    // Loop over fPiledTrackList
    // |   Sub-step 1: Complete 3D pattern recognition
    void HoughTransformSZ(const std::pair<double, double>& center, const std::vector<HitPtr*>* piledTracks);
    void FindExceedThresholdSZ(const std::pair<double, double>& center);
    // |   Sub-step 2: Fit
    // |   Loop over fTrackList
    // |   |   Sub-sub-step 1
    void FitAndDumpToResult(const HelixParameters& parameters, const std::vector<HitPtr*>* track);
    // |   End loop
    // End loop
    // Step 3: Generate omitted list
    void GenerateOmitted();

    double ToPhiReal(Eigen::Index i) const { return -M_PI + (i + 0.5) * fPhiResolution; }
    double ToRhoReal(Eigen::Index j) const { return fRhoLow + (j + 0.5) * fRhoResolution; }
    Eigen::Index ToPhiIndex(double phi) const { return (phi + M_PI) / fPhiResolution; }
    Eigen::Index ToRhoIndex(double rho) const { return (rho - fRhoLow) / fRhoResolution; }

    double ToZ0Real(Eigen::Index i) const { return fZ0Low + (i + 0.5) * fZ0Resolution; }
    double ToAlphaReal(Eigen::Index j) const { return -M_PI + (j + 0.5) * fAlphaResolution; }
    Eigen::Index ToZ0Index(double z0) const { return (z0 - fZ0Low) / fZ0Resolution; }
    Eigen::Index ToAlphaIndex(double alpha) const { return (alpha + M_PI) / fAlphaResolution; }

    static size_t EffectiveSizeOf(const std::vector<HitPtr*>& hitPtrPtrList) { return std::count_if(hitPtrPtrList.begin(), hitPtrPtrList.end(), [](auto hitPtrPtr) { return !(*hitPtrPtr == nullptr); }); }

private:
    std::vector<HitPtr> fHitData;

    const double fRhoLow;
    const double fRhoUp;
    const double fPhiResolution;
    const double fRhoResolution;
    size_t fThresholdXY = 20;
    Eigen::Matrix<std::vector<HitPtr*>, Eigen::Dynamic, Eigen::Dynamic> fHoughSpaceXY;
    std::vector<std::pair<std::pair<double, double>, const std::vector<HitPtr*>*>> fPiledTrackList;

    const double fZ0Low;
    const double fZ0Up;
    const double fZ0Resolution;
    const double fAlphaResolution;
    size_t fThresholdSZ = 20;
    Eigen::Matrix<std::vector<HitPtr*>, Eigen::Dynamic, Eigen::Dynamic> fHoughSpaceSZ;
    std::vector<std::pair<HelixParameters, const std::vector<HitPtr*>*>> fTrackList;
};

#include "MACE/ReconTracks/Tracker/Hough.inl"
*/