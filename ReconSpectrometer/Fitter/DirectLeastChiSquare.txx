template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t>::
DirectLeastChiSquare() :
    Base() {}

template<class SpectromrterHit_t>
MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t>::
~DirectLeastChiSquare() {}

template<class SpectromrterHit_t>
bool MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t>::
Fit(const std::vector<HitPtr>& hitData, const std::optional<HelixParameters>&) {

}

template<class SpectromrterHit_t>
void MACE::ReconSpectrometer::Fitter::DirectLeastChiSquare<SpectromrterHit_t>::
SortHitsByCellID() {
    auto Comparsion = [](const HitPtr& hitPtr1, const HitPtr& hitPtr2)->bool {
        return hitPtr1->GetCellID() > hitPtr2->GetCellID();
    };
    std::sort(Base::fHitData.begin(), Base::fHitData.end(), Comparsion);
}
