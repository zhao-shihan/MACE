#pragma once

#include "MACEGlobal.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"

#define MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(Hit_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::SpectrometerHit, Hit_t>, \
        "The hit type should be derived from MACE::DataModel::SpectrometerHit")

#define MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(Hit_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::SpectrometerSimHit, Hit_t>, \
        "The hit type should be derived from MACE::DataModel::SpectrometerSimHit")

#define MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, Hit_t) \
    static_assert(std::is_base_of_v<MACE::ReconSpectrometer::Interface::Fitter<Hit_t>, FitterT_t<Hit_t>>, \
        "The fitter type should be derived from MACE::ReconSpectrometer::Interface::Fitter"); \
    static_assert(std::is_default_constructible_v<FitterT_t<Hit_t>>, \
        "The fitter type should be default constructible")
