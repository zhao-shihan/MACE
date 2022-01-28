#pragma once

#include "MACEGlobal.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"

#define MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(HitType) \
    static_assert(std::is_base_of_v<MACE::DataModel::SpectrometerHit, HitType>, \
        "The hit type should be derived from MACE::DataModel::SpectrometerHit")

#define MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterType, HitType) \
    static_assert(std::is_base_of_v<MACE::ReconSpectrometer::Interface::Fitter<HitType>, FitterType<HitType>>, \
        "The fitter type should be derived from MACE::ReconSpectrometer::Interface::Fitter")
