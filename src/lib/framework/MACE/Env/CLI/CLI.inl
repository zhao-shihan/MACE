namespace MACE::Env::CLI {

template<std::derived_from<ModuleBase>... AModules>
CLI<AModules...>::CLI() :
    CLI<>{},
    AModules{ArgParser()}... {}

} // namespace MACE::Env::CLI
