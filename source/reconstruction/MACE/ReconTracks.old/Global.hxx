#pragma once

#include "MACE/DataModel/Hit/CDCHit.hxx"
#include "MACE/DataModel/SimHit/CDCSimHit.hxx"
#include "MACE/DataModel/Track/CDCHelixTrack.hxx"
#include "MACE/DataModel/Track/CDCPhysicsTrack.hxx"

#include <iostream>

#define MACE_RECONSPECTROMETER_SPECTROMETERHIT_CONCEPT(Hit_t)                   \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::CDCHit, Hit_t>, \
                  "The hit type should be or derived from "                     \
                  "MACE::Core::DataModel::CDCHit")

#define MACE_RECONSPECTROMETER_SPECTROMETERSIMHIT_CONCEPT(Hit_t)                      \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::CDCSimHit, Hit_t>, \
                  "The hit type should be or derived from "                           \
                  "MACE::Core::DataModel::CDCSimHit")

#define MACE_RECONSPECTROMETER_TRACK_CONCEPT(Track_t)                                            \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::CDCHelixTrack, Track_t> or     \
                      std::is_base_of_v<MACE::Core::DataModel::CDCPhysicsTrack, Track_t>, \
                  "The track type should be or derived from "                                    \
                  "MACE::Core::DataModel::HelixTrack or "                                 \
                  "MACE::Core::DataModel::CDCPhysicsTrack");                              \
    static_assert(std::is_default_constructible_v<Track_t>,                                      \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_HELIXTRACK_CONCEPT(Track_t)                                 \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::CDCHelixTrack, Track_t>, \
                  "The track type should be or derived from "                              \
                  "MACE::Core::DataModel::HelixTrack");                             \
    static_assert(std::is_default_constructible_v<Track_t>,                                \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_PHYSICSTRACK_CONCEPT(Track_t)                                 \
    static_assert(std::is_base_of_v<MACE::Core::DataModel::CDCPhysicsTrack, Track_t>, \
                  "The track type should be or derived from "                                \
                  "MACE::Core::DataModel::CDCPhysicsTrack");                          \
    static_assert(std::is_default_constructible_v<Track_t>,                                  \
                  "The track type should be default constructible")

#define MACE_RECONSPECTROMETER_FITTER_CONCEPT(FitterT_t, Hit_t, Track_t)                                              \
    static_assert(std::is_base_of_v<MACE::ReconTracks::Interface::Fitter<Hit_t, Track_t>, FitterT_t<Hit_t, Track_t>>, \
                  "The fitter type should derived from "                                                              \
                  "MACE::ReconTracks::Interface::Fitter");                                                            \
    static_assert(std::is_default_constructible_v<FitterT_t<Hit_t, Track_t>>,                                         \
                  "The fitter type should be default constructible")

#define MACE_RECONSPECTROMETER_RECONSTRUCTOR_CONCEPT(Tracker_t, FitterT_t, Hit_t, Track_t)                                                   \
    static_assert(std::is_base_of_v<MACE::ReconTracks::Interface::Tracker<FitterT_t, Hit_t, Track_t>, Tracker_t<FitterT_t, Hit_t, Track_t>>, \
                  "The reconstructor type should derived from "                                                                              \
                  "MACE::ReconTracks::Interface::Tracker")
