#pragma once

#include "ReconSpectrometer/Global.hxx"

template<class SpectromrterHit_t, class Track_t>
class MACE::ReconSpectrometer::Interface::Fitter {
    MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(SpectromrterHit_t);
    MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t);

    Fitter(const Fitter&) = delete;
    Fitter& operator=(const Fitter&) = delete;

protected:
    using HitPtr = std::shared_ptr<SpectromrterHit_t>;
    using TrackPtr = std::shared_ptr<Track_t>;

    Fitter();
    virtual ~Fitter() noexcept = default;

public:
    virtual bool Fit(std::vector<HitPtr>& hitDataToBeFitted, TrackPtr& seed) = 0;
    [[nodiscard]] const auto& GetOmitted() const { return fOmittedList; }

protected:
    std::vector<HitPtr> fOmittedList;
};

#include "ReconSpectrometer/Interface/Fitter.ixx"
