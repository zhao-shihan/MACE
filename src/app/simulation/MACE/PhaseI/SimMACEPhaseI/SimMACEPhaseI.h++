#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

class SimMACEPhaseI : public Mustard::Application::Subprogram {
public:
    SimMACEPhaseI();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI
