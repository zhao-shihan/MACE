namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
GenFitDAF<AHit, ATrack>::GenFitDAF(double driftErrorRMS) :
    GenFitterBase<AHit, ATrack>{driftErrorRMS},
    fGenFitter{} {
    fGenFitter.setMultipleMeasurementHandling(genfit::weightedClosestToReferenceWire);
    fGenFitter.getKalman()->setMultipleMeasurementHandling(genfit::weightedClosestToReferenceWire);
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<std::indirectly_readable AHitPointer, std::indirectly_readable ASeedPointer>
    requires(Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit> and
             Mustard::Data::SuperTupleModel<typename std::iter_value_t<ASeedPointer>::Model, ATrack>)
auto GenFitDAF<AHit, ATrack>::operator()(const std::vector<AHitPointer>& hitData, ASeedPointer seed) -> std::pair<std::shared_ptr<Mustard::Data::Tuple<ATrack>>,
                                                                                                                                   std::vector<std::iter_value_t<AHitPointer>*>> {
    const auto [genfitTrack, measurementHitMap]{this->Initialize(hitData, seed)};
    if (genfitTrack == nullptr) { return {}; }

    try {
        fGenFitter.processTrack(genfitTrack.get(), true);
    } catch (const genfit::Exception&) {
        return {};
    }

    return this->Finalize(genfitTrack, seed, measurementHitMap);
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
