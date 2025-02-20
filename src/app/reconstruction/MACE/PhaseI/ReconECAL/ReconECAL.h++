#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::PhaseI::ReconECAL {

class ReconECAL : public Mustard::Application::Subprogram {
public:
    ReconECAL();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::PhaseI::ReconECAL
