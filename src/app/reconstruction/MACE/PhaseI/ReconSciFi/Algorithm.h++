// -*- C++ -*-
//
// Copyright (C) 2020-2025  MACESW developers
//
// This file is part of MACESW, Muonium-to-Antimuonium Conversion Experiment
// offline software.
//
// MACESW is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// MACESW is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// MACESW. If not, see <https://www.gnu.org/licenses/>.

#include "MACE/PhaseI/Data/Hit.h++"
#include "MACE/PhaseI/Data/SensorHit.h++"
#include "MACE/PhaseI/Data/SensorRawHit.h++"
#include "MACE/PhaseI/Data/SimHit.h++"
#include "MACE/PhaseI/Data/Track.h++"

#include "Mustard/Data/Tuple.h++"

#include "muc/array"

#include <algorithm>
#include <memory>
#include <vector>

namespace MACE::PhaseI::ReconSciFi {

auto FindCrossCoordinates(double lID, double rID, double tID, int lNumber, int rNumber, int tNumber, double x0, double y0)
    -> std::vector<muc::array3d>;

auto FindLayerID(int id) -> int;

auto HitNumber(std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>& data, double deltaTime)
    -> std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>;

template<typename... Args>
auto InSameSubarray(Args... args) -> bool;

auto DividedHit(const std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>& data, double deltaTime)
    -> std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>;

auto PositionTransform(const std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>& data)
    -> std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::ReconTrack>>>;

} // namespace MACE::PhaseI::ReconSciFi
