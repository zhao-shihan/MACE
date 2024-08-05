namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
GenFitterBase<AHit, ATrack>::GenFitterBase(double driftErrorRMS, double lowestMomentum) :
    fDriftErrorRMS{driftErrorRMS},
    fLowestMomentum{lowestMomentum},
    fEnableEventDisplay{false},
    fGeoManager{},
    fEventDisplayTrackStore{} {
    // geant4 geometry
    Detector::Definition::World world;
    Detector::Assembly::MMS mms{world, false};
    mms.Get<Detector::Definition::CDCGas>().RemoveDaughter<Detector::Definition::CDCSuperLayer>();
    // geant4 -> gdml
    const auto& mpiEnv{Mustard::Env::MPIEnv::Instance()};
    std::filesystem::path gdmlFSPath;
    std::filesystem::path::string_type gdmlPath;
    if (mpiEnv.OnCommNodeMaster()) {
        gdmlFSPath = Mustard::CreateTemporaryFile("mms_temp", ".gdml");
        world.Export(gdmlFSPath);
        gdmlPath = gdmlFSPath;
    }
    auto gdmlPathLength{gdmlPath.length()};
    MPI_Bcast(&gdmlPathLength, 1, Mustard::MPIX::DataType(gdmlPathLength), 0, mpiEnv.CommNode());
    gdmlPath.resize(gdmlPathLength);
    MPI_Bcast(gdmlPath.data(), gdmlPathLength, Mustard::MPIX::DataType(gdmlPath.data()), 0, mpiEnv.CommNode());
    // gdml -> root
    fGeoManager = std::unique_ptr<TGeoManager>{TGeoManager::Import(gdmlPath.c_str())};
    fGeoManager->GetTopVolume()->SetInvisible();
    // remove gdml
    MPI_Barrier(mpiEnv.CommNode());
    if (mpiEnv.OnCommNodeMaster()) {
        std::error_code ec;
        std::filesystem::remove(gdmlFSPath, ec);
    }
    // setup genfit
    genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface);
    genfit::FieldManager::getInstance()->init(new GenFitMMSField);
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<std::indirectly_readable AHitPointer, std::indirectly_readable ASeedPointer>
    requires(Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit> and
             Mustard::Data::SuperTupleModel<typename std::iter_value_t<ASeedPointer>::Model, ATrack>)
auto GenFitterBase<AHit, ATrack>::Initialize(const std::vector<AHitPointer>& hitData, ASeedPointer seed)
    -> std::pair<std::shared_ptr<genfit::Track>,
                 std::unordered_map<const genfit::AbsMeasurement*, std::iter_value_t<AHitPointer>*>> {
    if (Mustard::Math::Norm2(*Get<"p0">(*seed)) < muc::pow<2>(fLowestMomentum)) {
        return {};
    }
    if (TDatabasePDG::Instance()->GetParticle(Get<"PDGID">(*seed)) == nullptr) {
        return {};
    }

    const auto genfitTrack{
        std::make_shared<genfit::Track>(new genfit::RKTrackRep{Get<"PDGID">(*seed)}, // track rep will be deleted when genfit::Track destructs
                                        Mustard::ToG3<"Length">(this->ToTVector3(*Get<"x0">(*seed))),
                                        Mustard::ToG3<"Energy">(this->ToTVector3(*Get<"p0">(*seed))))};

    std::unordered_map<const genfit::AbsMeasurement*, std::iter_value_t<AHitPointer>*> measurementHitMap;
    measurementHitMap.reserve(hitData.size());

    const auto& cdc{Detector::Description::CDC::Instance()};
    const auto& cellMap{cdc.CellMap()};
    for (auto&& hit : hitData) {
        const auto& cell{cellMap.at(Get<"CellID">(*hit))};
        const Eigen::Vector3d wirePosition{cell.position.x(), cell.position.y(), 0};
        const Eigen::Vector3d wireStartPoint{wirePosition - cell.senseWireHalfLength * cell.direction};
        const Eigen::Vector3d wireEndPoint{wirePosition + cell.senseWireHalfLength * cell.direction};

        TVectorD rawHitCoords(7);
        rawHitCoords[0] = Mustard::ToG3<"Length">(wireStartPoint.x());
        rawHitCoords[1] = Mustard::ToG3<"Length">(wireStartPoint.y());
        rawHitCoords[2] = Mustard::ToG3<"Length">(wireStartPoint.z());
        rawHitCoords[3] = Mustard::ToG3<"Length">(wireEndPoint.x());
        rawHitCoords[4] = Mustard::ToG3<"Length">(wireEndPoint.y());
        rawHitCoords[5] = Mustard::ToG3<"Length">(wireEndPoint.z());
        rawHitCoords[6] = Mustard::ToG3<"Length">(*Get<"d">(*hit));

        TMatrixDSym rawHitCov(7);
        const auto varD{muc::pow<2>(Mustard::ToG3<"Length">(this->DriftErrorRMS()))};
        rawHitCov(0, 0) = varD;
        rawHitCov(1, 1) = varD;
        rawHitCov(2, 2) = varD;
        rawHitCov(3, 3) = varD;
        rawHitCov(4, 4) = varD;
        rawHitCov(5, 5) = varD;
        rawHitCov(6, 6) = varD;

        // clang-format off
        const auto measurement{new Measurement{rawHitCoords, rawHitCov,
                                               cell.cellID, Get<"HitID">(*hit),
                                               nullptr}}; // clang-format on
        genfitTrack->insertPoint(new genfit::TrackPoint{measurement, genfitTrack.get()});
        measurementHitMap.emplace(measurement, std::to_address(hit));
    }

    return {genfitTrack, measurementHitMap};
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<std::indirectly_readable AHitPointer, std::indirectly_readable ASeedPointer>
    requires(Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit> and
             Mustard::Data::SuperTupleModel<typename std::iter_value_t<ASeedPointer>::Model, ATrack>)
auto GenFitterBase<AHit, ATrack>::Finalize(std::shared_ptr<genfit::Track> genfitTrack, ASeedPointer seed,
                                           const std::unordered_map<const genfit::AbsMeasurement*, AHitPointer>& measurementHitMap)
    -> std::pair<std::shared_ptr<Mustard::Data::Tuple<ATrack>>,
                 std::vector<AHitPointer>> {
    const auto& status{*genfitTrack->getFitStatus()};
    if (not status.isFitConvergedPartially()) { return {}; }

    const genfit::MeasuredStateOnPlane* firstState;
    try {
        firstState = &genfitTrack->getFittedState();
    } catch (const genfit::Exception&) {
        return {};
    }

    const auto x0{Mustard::ToG4<"Length">(firstState->getPos())};
    const auto p0{Mustard::ToG4<"Energy">(firstState->getMom())};
    const auto mass{Mustard::ToG4<"Energy">(firstState->getMass())};
    const auto pdgID{firstState->getPDG()};
    const auto ek0{std::sqrt(p0.Mag2() + muc::pow<2>(mass)) - mass};

    const auto& allPoint{genfitTrack->getPointsWithMeasurement()};
    std::vector<const genfit::TrackPoint*> fittedPoint;
    fittedPoint.reserve(allPoint.size());
    for (const auto cardinalRep{genfitTrack->getCardinalRep()};
         auto&& point : allPoint) {
        if (point->hasFitterInfo(cardinalRep)) {
            fittedPoint.emplace_back(point);
        }
    }

    const auto& track{std::make_shared_for_overwrite<Mustard::Data::Tuple<ATrack>>()};
    Get<"EvtID">(*track) = Get<"EvtID">(*seed);
    Get<"TrkID">(*track) = Get<"TrkID">(*seed);
    Get<"HitID">(*track)->resize(fittedPoint.size());
    std::ranges::transform(fittedPoint, Get<"HitID">(*track)->begin(),
                           [](auto&& p) { return p->getRawMeasurement()->getHitId(); });
    Get<"chi2">(*track) = status.getChi2() / status.getNdf();
    Get<"t0">(*track) = Get<"t0">(*seed);
    Get<"PDGID">(*track) = pdgID;
    Get<"x0">(*track) = this->template FromTVector3<muc::array3d>(x0);
    Get<"Ek0">(*track) = ek0;
    Get<"p0">(*track) = this->template FromTVector3<muc::array3d>(p0);
    Data::CalculateHelix(*track, Detector::Description::MMSField::Instance().FastField());

    std::vector<std::iter_value_t<AHitPointer>*> trackHit(fittedPoint.size());
    std::ranges::transform(fittedPoint, trackHit.begin(),
                           [&](auto&& p) { return measurementHitMap.at(p->getRawMeasurement()); });

    if (fEnableEventDisplay) {
        genfit::EventDisplay::getInstance()->addEvent(genfitTrack.get());
        fEventDisplayTrackStore.emplace_back(std::move(genfitTrack)); // genfitTrack is MOVED here
    }

    return {track, trackHit};
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
auto GenFitterBase<AHit, ATrack>::OpenEventDisplay(bool clearUponClose) -> void {
    genfit::EventDisplay::getInstance()->open();
    if (clearUponClose) { ClearEventDisplayTrackStore(); }
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<Mustard::Concept::NumericVector3FloatingPoint T>
MUSTARD_ALWAYS_INLINE auto GenFitterBase<AHit, ATrack>::ToTVector3(T src) -> TVector3 {
    TVector3 dest;
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
template<Mustard::Concept::NumericVector3FloatingPoint T>
MUSTARD_ALWAYS_INLINE auto GenFitterBase<AHit, ATrack>::FromTVector3(const TVector3& src) -> T {
    T dest;
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter
