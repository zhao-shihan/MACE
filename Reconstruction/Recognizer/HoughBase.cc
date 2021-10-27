#include "Reconstruction/Recognizer/HoughBase.hh"

using namespace MACE::Reconstruction::Recognizer;
using namespace MACE::DataModel::Hit;

HoughBase::HoughBase(Eigen::Index rows, Eigen::Index cols) :
    fRows(rows),
    fCols(cols),
    fHoughStore(rows, cols),
    fHoughSpace(rows, cols),
    fCenterCandidateList(0),
    fCenterClusterList(0),
    fRecognizedTrackList(0) {
    std::for_each_n(fHoughStore.data(), fRows * fCols, [](SpectrometerHitPointerList& elem) { elem.reserve(128UL); });
    fCenterClusterList.reserve(64UL);
    fRecognizedTrackList.reserve(64UL);
}

HoughBase::~HoughBase() {}

void HoughBase::Recognize() {
    Initialize();
    HoughTransform();
    VoteForCenter();
    CenterClusterizaion();
    GenerateResult();
}

void HoughBase::Initialize() {
    std::for_each_n(fHoughStore.data(), fRows * fCols, [](SpectrometerHitPointerList& elem) { elem.clear(); });
    fHoughSpace.fill(0);
    fCenterCandidateList.clear();
    fCenterClusterList.clear();
    fRecognizedTrackList.clear();
}