#pragma once

#include "MACE/Env/CLI/CLI.h++"
#include "MACE/Env/CLI/Module/BasicModule.h++"
#include "MACE/Env/CLI/Module/Geant4Module.h++"
#include "MACE/Env/CLI/Module/MonteCarloModule.h++"

namespace MACE::Env::CLI {

using Geant4CLI = CLI<BasicModule,
                      MonteCarloModule,
                      Geant4Module>;

} // namespace MACE::Env::CLI
