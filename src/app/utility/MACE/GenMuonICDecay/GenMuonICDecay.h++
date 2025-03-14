#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::GenMuonICDecay {

class GenMuonICDecay : public Mustard::Application::Subprogram {
public:
    GenMuonICDecay();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::GenMuonICDecay
