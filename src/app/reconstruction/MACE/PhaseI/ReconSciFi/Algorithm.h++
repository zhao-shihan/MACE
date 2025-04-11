#include "MACE/PhaseI/Data/Hit.h++"
#include "MACE/PhaseI/Data/SensorHit.h++"
#include "MACE/PhaseI/Data/SensorRawHit.h++"
#include "MACE/PhaseI/Data/SimHit.h++"
#include "MACE/PhaseI/Data/Track.h++"
#include "MACE/PhaseI/Detector/Description/SciFiTracker.h++"

#include "Mustard/Data/Tuple.h++"

#include "muc/algorithm"
#include "muc/array"

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <numbers>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MACE::PhaseI::ReconSciFi {

auto FindCrossCoordinates(double lID, double rID, double tID, int lNumber, int rNumber, int tNumber, double x0, double y0)
    -> std::vector<muc::array3d>;

auto GetLayerID(int id) -> int;

auto HitNumber(std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>& data, double deltaTime)
    -> std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>;

template<typename... Args>
bool AreInSameSubarray(Args... args);

auto DividedHit(const std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>& data, double deltaTime)
    -> std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>>;

auto PositionTransform(const std::vector<std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::SiPMHit>>>> data)
    -> std::vector<std::shared_ptr<Mustard::Data::Tuple<MACE::PhaseI::Data::ReconTrack>>>;

} // namespace MACE::PhaseI::ReconSciFi
