#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimMMS {

class SimMMS : public Mustard::Application::Subprogram {
public:
    SimMMS();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimMMS
