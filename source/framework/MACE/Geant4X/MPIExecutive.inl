namespace MACE::Geant4X {

template<class AMacroOrCommand>
void MPIExecutive::StartSession(const Geant4CLI& cli, AMacroOrCommand&& macroOrCommands) const {
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
#if MACE_WITH_G4VIS
    G4UIExecutive uiExecutive(argc, argv);
    G4VisExecutive visExecutive;
    visExecutive.Initialize();
#else
    G4UIExecutive uiExecutive(argc, argv, "tcsh");
#endif
    Execute(std::forward<AMacroOrCommand>(macroOrCommands));
    uiExecutive.SessionStart();
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
