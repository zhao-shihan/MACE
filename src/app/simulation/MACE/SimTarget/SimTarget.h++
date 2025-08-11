#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimTarget {

class SimTarget : public Mustard::Application::Subprogram {
public:
    SimTarget();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimTarget
