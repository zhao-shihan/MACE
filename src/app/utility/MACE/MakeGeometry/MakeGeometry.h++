#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::MakeGeometry {

class MakeGeometry : public Mustard::Application::Subprogram {
public:
    MakeGeometry();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::MakeGeometry
