namespace MACE::Geant4X {

void MPIExecutive::StartSession(const Geant4CLI& cli, auto&& macOrCMDs) const {
    if (cli.IsInteractive()) {
        auto&& [argc, argv] = cli.GetArgcArgv();
        if (cli.GetMacro().empty()) {
            StartInteractiveSession(argc, argv, std::forward<decltype(macOrCMDs)>(macOrCMDs));
        } else {
            StartInteractiveSession(argc, argv, cli.GetMacro());
        }
    } else {
        StartBatchSession(cli.GetMacro());
    }
}

void MPIExecutive::StartInteractiveSession(int argc, char* argv[], auto&& macOrCMDs) const {
    CheckSequential();
#if MACE_USE_G4VIS
    G4UIExecutive uiExecutive(argc, argv);
    G4VisExecutive visExecutive;
    visExecutive.Initialize();
#else
    G4UIExecutive uiExecutive(argc, argv, "tcsh");
#endif
    Execute(std::forward<decltype(macOrCMDs)>(macOrCMDs));
    uiExecutive.SessionStart();
}

void MPIExecutive::Execute(const std::ranges::range auto& cmdText) requires
    std::convertible_to<typename std::remove_cvref_t<decltype(cmdText)>::value_type, std::string> {
    for (auto&& command : cmdText) {
        if (not ExecuteCommand(std::forward<decltype(command)>(command))) { break; }
    }
}

} // namespace MACE::Geant4X
