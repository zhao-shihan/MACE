namespace MACE::SimulationG4 {

template<class AMacroOrCommand>
void MPIExecutive::StartSession(const SimulationG4CLI& cli, AMacroOrCommand&& macroOrCommands) const {
    if (cli.IsInteractive()) {
        auto&& [argc, argv] = cli.GetArgcArgv();
        if (cli.GetMacro().empty()) {
            StartInteractiveSession(argc, argv, std::forward<AMacroOrCommand>(macroOrCommands));
        } else {
            StartInteractiveSession(argc, argv, cli.GetMacro());
        }
    } else {
        StartBatchSession(cli.GetMacro());
    }
}

template<class AMacroOrCommand>
void MPIExecutive::StartInteractiveSession(int argc, char* argv[], AMacroOrCommand&& macroOrCommands) const {
    CheckSequential();
    const auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
    const auto visExecutive = std::make_unique<G4VisExecutive>();
    visExecutive->Initialize();
    Execute(std::forward<AMacroOrCommand>(macroOrCommands));
    uiExecutive->SessionStart();
}

template<std::ranges::range ARange> // clang-format off
    requires std::convertible_to<typename ARange::value_type, std::string>
void MPIExecutive::Execute(const ARange& commandList)  { // clang-format on
    for (auto&& command : commandList) {
        if (not ExecuteCommand(command)) { break; }
    }
}

template<std::convertible_to<std::string>... AStrings>
void MPIExecutive::Execute(const std::tuple<AStrings...>& commandList) {
    auto breaked = false;
    Utility::TupleForEach(commandList,
                          [&breaked](const auto& command) {
                              if (not breaked) {
                                  if (not ExecuteCommand(command)) { breaked = true; }
                              }
                          });
}

} // namespace MACE::SimulationG4
