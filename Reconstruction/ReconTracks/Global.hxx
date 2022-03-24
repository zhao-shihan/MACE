#pragma once

#include "DataModel/Hit/SpectrometerHit.hxx"
#include "DataModel/SimHit/SpectrometerSimHit.hxx"
#include "DataModel/Track/HelixTrack.hxx"
#include "DataModel/Track/PhysicsTrack.hxx"

#include <iostream>

#define MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(Hit_t)                            \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::Hit::SpectrometerHit, Hit_t>, \
                  "The hit type should be or derived from "                              \
                  "MACE::Core::DataModel::SpectrometerHit")

#define MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(Hit_t)                               \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::SimHit::SpectrometerSimHit, Hit_t>, \
                  "The hit type should be or derived from "                                    \
                  "MACE::Core::DataModel::SpectrometerSimHit")

#define MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t)                                         \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::Track::HelixTrack, Track_t> or     \
                      std::is_base_of_v<MACE::Core::DataModel::Track::PhysicsTrack, Track_t>, \
                  "The track type should be or derived from "                                 \
                  "MACE::Core::DataModel::Track::HelixTrack or "                              \
                  "MACE::Core::DataModel::Track::PhysicsTrack");                              \
    static_assert(std::is_default_constructible_v<Track_t>,                                   \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t)                              \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::Track::HelixTrack, Track_t>, \
                  "The track type should be or derived from "                           \
                  "MACE::Core::DataModel::Track::HelixTrack");                          \
    static_assert(std::is_default_constructible_v<Track_t>,                             \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_PHYSICSTRACK_CONCEPT(Track_t)                              \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::Track::PhysicsTrack, Track_t>, \
                  "The track type should be or derived from "                             \
                  "MACE::Core::DataModel::Track::PhysicsTrack");                          \
    static_assert(std::is_default_constructible_v<Track_t>,                               \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, Hit_t, Track_t)                                                              \
    static_assert(std::is_base_of_v<MACE::Reconstruction::ReconTracks::Interface::Fitter<Hit_t, Track_t>, FitterT_t<Hit_t, Track_t>>, \
                  "The fitter type should derived from "                                                                              \
                  "MACE::Reconstruction::ReconTracks::Interface::Fitter");                                                            \
    static_assert(std::is_default_constructible_v<FitterT_t<Hit_t, Track_t>>,                                                         \
                  "The fitter type should be default constructible")

#define MACE_RECONSPECTROMETER_RECONSTRUCTOR_CONCEPT(Tracker_t, FitterT_t, Hit_t, Track_t)                                                                   \
    static_assert(std::is_base_of_v<MACE::Reconstruction::ReconTracks::Interface::Tracker<FitterT_t, Hit_t, Track_t>, Tracker_t<FitterT_t, Hit_t, Track_t>>, \
                  "The reconstructor type should derived from "                                                                                              \
                  "MACE::Reconstruction::ReconTracks::Interface::Tracker")
