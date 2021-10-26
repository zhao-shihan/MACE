#include "Reconstruction/Recognizer/HoughBase.hh"

using namespace MACE::Reconstruction::Recognizer;
using namespace MACE::DataModel::Hit;

HoughBase::HoughBase(Eigen::Index size) :
    fSize(size),
    fHoughStore(size, size),
    fHoughSpace(size, size),
    fCenterCandidateList(0),
    fCenterClusterList(0),
    fRecognizedTrackList(0) {
    std::for_each_n(fHoughStore.data(), fSize * fSize, [](SpectrometerHitPointerList& elem) { elem.reserve(128UL); });
    fCenterClusterList.reserve(64UL);
    fRecognizedTrackList.reserve(64UL);
}

HoughBase::~HoughBase() {}