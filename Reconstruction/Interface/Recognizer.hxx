#pragma once

#include "DataModel/Hit/SpectrometerHit.hxx"
#include "Reconstruction/Global.hxx"

template<class SpectrometerHitType>
class MACE::Reconstruction::Interface::Recognizer {
    static_assert(std::is_base_of_v<DataModel::SpectrometerHit, SpectrometerHitType>,
        "SpectrometerHitType should be derived from MACE::DataModel::Hit::SpectrometerHit");

    Recognizer(const Recognizer&) = delete;
    Recognizer& operator=(const Recognizer&) = delete;

protected:
    using Hit = std::shared_ptr<SpectrometerHitType>;

    Recognizer();
    virtual ~Recognizer();

public:
    virtual void Recognize(const std::vector<Hit>& hitList) = 0;
    const auto& GetRecognizedTrackList() const { return fRecognizedList; }

protected:
    std::vector<std::vector<Hit>> fRecognizedList;
};

#include "Reconstruction/Interface/Recognizer.txx"