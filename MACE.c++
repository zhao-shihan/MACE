#include "MACE/PhaseI/PhaseI.h++"
#include "MACE/ReconECAL/ReconECAL.h++"
#include "MACE/ReconMMSTrack/ReconMMSTrack.h++"
#include "MACE/SimDose/SimDose.h++"
#include "MACE/SimECAL/SimECAL.h++"
#include "MACE/SimMACE/SimMACE.h++"
#include "MACE/SimMMS/SimMMS.h++"
#include "MACE/SimPTS/SimPTS.h++"
#include "MACE/SimTarget/SimTarget.h++"
#include "MACE/SmearMACE/SmearMACE.h++"

#include "Mustard/Application/SubprogramLauncher.h++"

auto main(int argc, char* argv[]) -> int {
    Mustard::Application::SubprogramLauncher launcher;
    launcher.AddSubprogram<MACE::PhaseI::PhaseI>();
    launcher.AddSubprogram<MACE::ReconECAL::ReconECAL>();
    launcher.AddSubprogram<MACE::ReconMMSTrack::ReconMMSTrack>();
    launcher.AddSubprogram<MACE::SimDose::SimDose>();
    launcher.AddSubprogram<MACE::SimECAL::SimECAL>();
    launcher.AddSubprogram<MACE::SimMACE::SimMACE>();
    launcher.AddSubprogram<MACE::SimMMS::SimMMS>();
    launcher.AddSubprogram<MACE::SimPTS::SimPTS>();
    launcher.AddSubprogram<MACE::SimTarget::SimTarget>();
    launcher.AddSubprogram<MACE::SmearMACE::SmearMACE>();
    return launcher.LaunchMain(argc, argv);
}
