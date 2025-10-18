#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SimVeto {

class SimVeto : public Mustard::Application::Subprogram {
public:
    SimVeto();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SimVeto
