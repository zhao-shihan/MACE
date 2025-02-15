#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimPTS {

class SimPTS : public Mustard::Application::Subprogram {
public:
    SimPTS();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimPTS
