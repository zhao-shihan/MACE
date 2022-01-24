#pragma once

#include "DataModel/Hit/SpectrometerHit.hxx"
#include "ReconSpectrometer/Global.hxx"

template<class SpectrometerHitType>
class MACE::ReconSpectrometer::Interface::Reconstructor {
    static_assert(std::is_base_of_v<DataModel::SpectrometerHit, SpectrometerHitType>,
        "SpectrometerHitType should be derived from MACE::DataModel::Hit::SpectrometerHit");

    Reconstructor(const Reconstructor&) = delete;
    Reconstructor& operator=(const Reconstructor&) = delete;

protected:
    using Hit = std::shared_ptr<SpectrometerHitType>;

    Reconstructor();
    virtual ~Reconstructor();

public:
    virtual void Recognize(const std::vector<Hit>& hitList) = 0;
    const auto& GetRecognizedTrackList() const { return fRecognizedList; }

protected:
    std::vector<std::vector<Hit>> fRecognizedList;
};

#include "ReconSpectrometer/Interface/Reconstructor.txx"