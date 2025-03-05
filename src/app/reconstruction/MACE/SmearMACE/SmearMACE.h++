#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::SmearMACE {

class SmearMACE : public Mustard::Application::Subprogram {
public:
    SmearMACE();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::SmearMACE
