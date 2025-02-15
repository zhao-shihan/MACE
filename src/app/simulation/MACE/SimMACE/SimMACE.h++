#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimMACE {

class SimMACE : public Mustard::Application::Subprogram {
public:
    SimMACE();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimMACE
