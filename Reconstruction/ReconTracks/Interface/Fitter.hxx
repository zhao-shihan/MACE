#pragma once

#include "Reconstruction/ReconTracks/Global.hxx"

namespace MACE::Reconstruction::ReconTracks::Interface {

template<class SpectrometerHit_t, class Track_t>
class Fitter {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectrometerHit_t);
    MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t);

    Fitter(const Fitter&) = delete;
    Fitter& operator=(const Fitter&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectrometerHit_t>;

    Fitter();
    virtual ~Fitter() noexcept = default;

public:
    virtual bool Fit(std::vector<HitPtr>& hitDataToBeFitted, Track_t& seed) = 0;
    [[nodiscard]] const auto& GetOmitted() const { return fOmittedList; }

    void SetVerbose(int verbose) { fVerbose = verbose; }

protected:
    std::vector<HitPtr> fOmittedList;

    int fVerbose = 1;
};

} // namespace MACE::Reconstruction::ReconTracks::Interface

#include "Reconstruction/ReconTracks/Interface/Fitter.ixx"
