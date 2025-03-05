#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::GenMuoniumICDecay {

class GenMuoniumICDecay : public Mustard::Application::Subprogram {
public:
    GenMuoniumICDecay();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::GenMuoniumICDecay
