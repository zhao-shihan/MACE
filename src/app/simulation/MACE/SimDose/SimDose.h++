#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimDose {

class SimDose : public Mustard::Application::Subprogram {
public:
    SimDose();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimDose
