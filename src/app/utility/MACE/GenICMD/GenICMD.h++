#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::GenICMD {

class GenICMD : public Mustard::Application::Subprogram {
public:
    GenICMD();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::GenICMD
