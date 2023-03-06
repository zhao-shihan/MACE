namespace MACE::Geant4X {

void MPIExecutive::StartSession(const Geant4CLI& cli, auto&& macFileOrCmdList) const {
    StartSessionImpl(cli, std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
}

template<typename T>
void MPIExecutive::StartSession(const Geant4CLI& cli, std::initializer_list<T> cmdList) const {
    StartSessionImpl(cli, cmdList);
}

void MPIExecutive::StartSession(int argc, char* argv[], auto&& macFileOrCmdList) const {
    StartSessionImpl(argc, argv, std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
}

template<typename T>
void MPIExecutive::StartSession(int argc, char* argv[], std::initializer_list<T> cmdList) const {
    StartSessionImpl(argc, argv, cmdList);
}

void MPIExecutive::StartInteractiveSession(int argc, char* argv[], auto&& macFileOrCmdList) const {
    StartInteractiveSessionImpl(argc, argv, std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
}

template<typename T>
void MPIExecutive::StartInteractiveSession(int argc, char* argv[], std::initializer_list<T> cmdList) const {
    StartInteractiveSessionImpl(argc, argv, cmdList);
}

void MPIExecutive::StartBatchSession(auto&& macFileOrCmdList) const {
    StartBatchSessionImpl(std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
}

template<typename T>
void MPIExecutive::StartBatchSession(std::initializer_list<T> cmdList) const {
    StartBatchSessionImpl(cmdList);
}

void MPIExecutive::StartSessionImpl(const Geant4CLI& cli, auto&& macFileOrCmdList) const {
    if (cli.IsInteractive()) {
        auto&& [argc, argv] = cli.GetArgcArgv();
        if (cli.GetMacro().empty()) {
            StartInteractiveSessionImpl(argc, argv, std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
        } else {
            StartInteractiveSessionImpl(argc, argv, cli.GetMacro());
        }
    } else {
        StartBatchSessionImpl(cli.GetMacro());
    }
}

void MPIExecutive::StartInteractiveSessionImpl(int argc, char* argv[], auto&& macFileOrCmdList) const {
    CheckSequential();
#if MACE_USE_G4VIS
    G4UIExecutive uiExecutive(argc, argv);
    G4VisExecutive visExecutive;
    visExecutive.Initialize();
#else
    G4UIExecutive uiExecutive(argc, argv, "tcsh");
#endif
    Execute(std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
    uiExecutive.SessionStart();
}

void MPIExecutive::StartBatchSessionImpl(auto&& macFileOrCmdList) const {
    Execute(std::forward<decltype(macFileOrCmdList)>(macFileOrCmdList));
}

void MPIExecutive::Execute(const std::ranges::input_range auto& cmdList)
    requires std::convertible_to<typename std::remove_cvref_t<decltype(cmdList)>::value_type, std::string>
{
    for (auto&& command : cmdList) {
        if (const auto success = ExecuteCommand(std::forward<decltype(command)>(command));
            not success) { break; }
    }
}

} // namespace MACE::Geant4X
