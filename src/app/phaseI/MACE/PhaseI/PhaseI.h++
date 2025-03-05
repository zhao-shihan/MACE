#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::PhaseI {

class PhaseI : public Mustard::Application::Subprogram {
public:
    PhaseI();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::PhaseI
