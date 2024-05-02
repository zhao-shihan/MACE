#include "MACE/Env/CLI/Module/ModuleBase.h++"

namespace MACE::Env::CLI::inline Module {

ModuleBase::ModuleBase(argparse::ArgumentParser& argParser) :
    NonMoveableBase{},
    fArgParser{&argParser} {}

} // namespace MACE::Env::CLI::inline Module
