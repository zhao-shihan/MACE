#pragma once

#include "DataModel/Hit/SpectrometerHit.hxx"
#include "ReconSpectrometer/Global.hxx"

class MACE::ReconSpectrometer::Interface::Reconstructor {
    Reconstructor(const Reconstructor&) = delete;
    Reconstructor& operator=(const Reconstructor&) = delete;

protected:
    using HitType = DataModel::SpectrometerHit;
    using Hit = std::shared_ptr<HitType>;

    Reconstructor();
    virtual ~Reconstructor();

public:
    void SetHitDataToBeRecongnized(const std::vector<Hit>& hitData) { fHitData = hitData; }
    template<class SpectrometerHitType>
    void SetHitDataToBeRecongnized(const std::vector<std::shared_ptr<SpectrometerHitType>>& hitData);

    virtual void Recognize() = 0;

    template<class SpectrometerHitType = HitType>
    std::vector<std::vector<std::shared_ptr<SpectrometerHitType>>> GetRecognizedTrackList();

protected:
    std::vector<Hit> fHitData;
    std::vector<std::vector<Hit>> fRecognizedTrackList;
};

template<class SpectrometerHitType>
void MACE::ReconSpectrometer::Interface::Reconstructor::
SetHitDataToBeRecongnized(const std::vector<std::shared_ptr<SpectrometerHitType>>& hitData) {
    static_assert(std::is_base_of_v<HitType, SpectrometerHitType>,
        "SpectrometerHitType should be derived from MACE::DataModel::Hit::SpectrometerHit");
    fHitData.clear();
    fHitData.reserve(hitData.size());
    for (auto&& hit : hitData) {
        fHitData.emplace_back(std::static_pointer_cast<HitType>(hit));
    }
}

template<>
inline std::vector<std::vector<MACE::ReconSpectrometer::Interface::Reconstructor::Hit>> MACE::ReconSpectrometer::Interface::Reconstructor::
GetRecognizedTrackList<MACE::ReconSpectrometer::Interface::Reconstructor::HitType>() {
    return fRecognizedTrackList;
}

template<class SpectrometerHitType>
std::vector<std::vector<std::shared_ptr<SpectrometerHitType>>> MACE::ReconSpectrometer::Interface::Reconstructor::
GetRecognizedTrackList() {
    static_assert(std::is_base_of_v<HitType, SpectrometerHitType>,
        "SpectrometerHitType should be derived from MACE::DataModel::Hit::SpectrometerHit");
    std::vector<std::vector<std::shared_ptr<SpectrometerHitType>>> recognizedTrackList(fRecognizedTrackList.size());
    for (size_t i = 0; i < fRecognizedTrackList.size(); ++i) {
        const auto& srcTrack = fRecognizedTrackList[i];
        auto& dstTrack = recognizedTrackList[i];
        dstTrack.reserve(srcTrack.size());
        for (size_t j = 0; j < srcTrack.size(); ++j) {
            dstTrack.emplace_back(std::static_pointer_cast<SpectrometerHitType>(srcTrack[j]));
        }
    }
    return recognizedTrackList;
}