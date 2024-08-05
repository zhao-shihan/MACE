#pragma once

#include "MACE/Data/Hit.h++"
#include "MACE/Data/MMSTrack.h++"
#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Reconstruction/MMSTracking/Field/GenFitMMSField.h++"
#include "MACE/Reconstruction/MMSTracking/Fitter/FitterBase.h++"

#include "Mustard/Concept/NumericVector.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/MPIX/DataType.h++"
#include "Mustard/Math/Norm.h++"
#include "Mustard/Utility/ConvertG3G4Unit.h++"
#include "Mustard/Utility/CreateTemporaryFile.h++"
#include "Mustard/Utility/InlineMacro.h++"

#include "AbsMeasurement.h"
#include "EventDisplay.h"
#include "FieldManager.h"
#include "FitStatus.h"
#include "MaterialEffects.h"
#include "MeasuredStateOnPlane.h"
#include "RKTrackRep.h"
#include "StateOnPlane.h"
#include "Track.h"
#include "TrackPoint.h"
#include "WireMeasurement.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include "TDatabasePDG.h"
#include "TGeoManager.h"
#include "TGeoMaterialInterface.h"
#include "TMatrixDSymfwd.h"
#include "TMatrixTSym.h"
#include "TVector3.h"
#include "TVectorD.h"

#include "mpi.h"

#include "muc/math"

#include <iterator>
#include <memory>
#include <utility>
#include <vector>

namespace MACE::inline Reconstruction::MMSTracking::inline Fitter {

template<Mustard::Data::SuperTupleModel<Data::CDCHit> AHit,
         Mustard::Data::SuperTupleModel<Data::MMSTrack> ATrack>
class GenFitterBase : public FitterBase<AHit, ATrack> {
public:
    using Measurement = genfit::WireMeasurement;

protected:
    GenFitterBase(double driftErrorRMS, double lowestMomentum = 1 * CLHEP::MeV);
    virtual ~GenFitterBase() = default;

public:
    auto DriftErrorRMS() const -> auto { return fDriftErrorRMS; }
    auto LowestMomentum() const -> auto { return fLowestMomentum; }
    auto EnableEventDisplay() const -> auto { return fEnableEventDisplay; }

    auto DriftErrorRMS(double val) -> void { fDriftErrorRMS = val; }
    auto LowestMomentum(double val) -> void { fLowestMomentum = val; }
    auto EnableEventDisplay(bool val) -> void { fEnableEventDisplay = val; }

    auto OpenEventDisplay(bool clearUponClose = true) -> void;
    auto ClearEventDisplayTrackStore() -> void { fEventDisplayTrackStore.clear(); }

protected:
    template<std::indirectly_readable AHitPointer, std::indirectly_readable ASeedPointer>
        requires(Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit> and
                 Mustard::Data::SuperTupleModel<typename std::iter_value_t<ASeedPointer>::Model, ATrack>)
    auto Initialize(const std::vector<AHitPointer>& hitData, ASeedPointer seed)
        -> std::pair<std::shared_ptr<genfit::Track>,
                     std::unordered_map<const genfit::AbsMeasurement*, std::iter_value_t<AHitPointer>*>>;
    template<std::indirectly_readable AHitPointer, std::indirectly_readable ASeedPointer>
        requires(Mustard::Data::SuperTupleModel<typename std::iter_value_t<AHitPointer>::Model, AHit> and
                 Mustard::Data::SuperTupleModel<typename std::iter_value_t<ASeedPointer>::Model, ATrack>)
    auto Finalize(std::shared_ptr<genfit::Track> genfitTrack, ASeedPointer seed,
                  const std::unordered_map<const genfit::AbsMeasurement*, AHitPointer>& measurementHitMap)
        -> std::pair<std::shared_ptr<Mustard::Data::Tuple<ATrack>>,
                     std::vector<AHitPointer>>;

    template<Mustard::Concept::NumericVector3FloatingPoint T>
    MUSTARD_ALWAYS_INLINE static auto ToTVector3(T src) -> TVector3;
    template<Mustard::Concept::NumericVector3FloatingPoint T>
    MUSTARD_ALWAYS_INLINE static auto FromTVector3(const TVector3& src) -> T;

private:
    double fDriftErrorRMS;
    double fLowestMomentum;
    bool fEnableEventDisplay;

    std::unique_ptr<TGeoManager> fGeoManager;
    std::vector<std::shared_ptr<genfit::Track>> fEventDisplayTrackStore;
};

} // namespace MACE::inline Reconstruction::MMSTracking::inline Fitter

#include "MACE/Reconstruction/MMSTracking/Fitter/GenFitterBase.inl"
