#pragma once

#include <iostream>

#include "CoreForwardDeclaration.hxx"
#include "ReconForwardDeclaration.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"
#include "DataModel/SimHit/SpectrometerSimHit.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"

#define MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(Hit_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::SpectrometerHit, Hit_t>, \
        "The hit type should be or derived from " \
            "MACE::DataModel::SpectrometerHit")

#define MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(Hit_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::SpectrometerSimHit, Hit_t>, \
        "The hit type should be or derived from " \
            "MACE::DataModel::SpectrometerSimHit")

#define MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::HelixTrack, Track_t> or \
                  std::is_base_of_v<MACE::DataModel::PhysicsTrack, Track_t>, \
        "The track type should be or derived from " \
            "MACE::DataModel::HelixTrack or " \
            "MACE::DataModel::PhysicsTrack"); \
    static_assert(std::is_default_constructible_v<Track_t>, \
        "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::HelixTrack, Track_t>, \
        "The track type should be or derived from " \
            "MACE::DataModel::HelixTrack"); \
    static_assert(std::is_default_constructible_v<Track_t>, \
        "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_PHYSICSTRACK_CONCEPT(Track_t) \
    static_assert(std::is_base_of_v<MACE::DataModel::PhysicsTrack, Track_t>, \
        "The track type should be or derived from " \
            "MACE::DataModel::PhysicsTrack"); \
    static_assert(std::is_default_constructible_v<Track_t>, \
        "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, Hit_t, Track_t) \
    static_assert(std::is_base_of_v<MACE::ReconSpectrometer::Interface::Fitter<Hit_t, Track_t>, FitterT_t<Hit_t, Track_t>>, \
        "The fitter type should derived from " \
            "MACE::ReconSpectrometer::Interface::Fitter"); \
    static_assert(std::is_default_constructible_v<FitterT_t<Hit_t, Track_t>>, \
        "The fitter type should be default constructible")

#define MACE_RECONSPECTROMETER_RECONSTRUCTOR_CONCEPT(Tracker_t, FitterT_t, Hit_t, Track_t) \
    static_assert(std::is_base_of_v<MACE::ReconSpectrometer::Interface::Tracker<FitterT_t, Hit_t, Track_t>, Tracker_t<FitterT_t, Hit_t, Track_t>>, \
        "The reconstructor type should derived from " \
            "MACE::ReconSpectrometer::Interface::Tracker")
