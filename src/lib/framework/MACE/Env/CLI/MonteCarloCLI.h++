#pragma once

#include "MACE/Env/CLI/CLI.h++"
#include "MACE/Env/CLI/Module/BasicModule.h++"
#include "MACE/Env/CLI/Module/MonteCarloModule.h++"

namespace MACE::Env::CLI {

using Geant4CLI = CLI<BasicModule,
                      MonteCarloModule>;

} // namespace MACE::Env::CLI
