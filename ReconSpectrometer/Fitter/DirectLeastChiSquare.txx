template<class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t, Track_t>::
DirectLeastChiSquare() :
    Base() {}

template<class SpectromrterHit_t, class Track_t>
MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t, Track_t>::
~DirectLeastChiSquare() {}

template<class SpectromrterHit_t, class Track_t>
bool MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t, Track_t>::
Fit(const std::vector<HitPtr>& hitData, const Track_t&) {

}

template<class SpectromrterHit_t, class Track_t>
void MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t, Track_t>::
SortHitsByCellID() {
    auto Comparsion = [](const HitPtr& hitPtr1, const HitPtr& hitPtr2)->bool {
        return hitPtr1->GetCellID() > hitPtr2->GetCellID();
    };
    std::sort(Base::fHitData.begin(), Base::fHitData.end(), Comparsion);
}
