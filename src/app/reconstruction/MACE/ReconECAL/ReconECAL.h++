#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::ReconECAL {

class ReconECAL : public Mustard::Application::Subprogram {
public:
    ReconECAL();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::ReconECAL
