#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::PhaseI::ReconSciFi {

class ReconSciFi : public Mustard::Application::Subprogram {
public:
    ReconSciFi();

    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::PhaseI::ReconSciFi
