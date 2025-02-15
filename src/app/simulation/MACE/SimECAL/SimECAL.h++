#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimECAL {

class SimECAL : public Mustard::Application::Subprogram {
public:
    SimECAL();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimECAL
