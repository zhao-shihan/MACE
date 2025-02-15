#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace MACE::ReconMMSTrack {

class ReconMMSTrack : public Mustard::Application::Subprogram {
public:
    ReconMMSTrack();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace MACE::ReconMMSTrack
