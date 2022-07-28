namespace MACE::SimulationG4 {

void MPIExecutive::StartInteractiveSession(int argc, char* argv[], const std::ranges::range auto& macroOrCommands) const {
    CheckSequential();
    const auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
    const auto visExecutive = std::make_unique<G4VisExecutive>();
    visExecutive->Initialize();
    if (not macroOrCommands.empty()) { Execute(macroOrCommands); }
    uiExecutive->SessionStart();
}

template<std::ranges::range ARange> // clang-format off
    requires std::convertible_to<typename ARange::value_type, std::string>
void MPIExecutive::Execute(const ARange& commandList) const { // clang-format on
    for (const std::string& command : commandList) {
        if (command.empty()) { continue; }
        if (command[command.find_first_not_of(' ')] == '#') { continue; }
        if (const auto commandStatus = fG4UIManager->ApplyCommand(command);
            commandStatus != fCommandSucceeded) [[unlikely]] {
            MACE_ENVIRONMENT_CONTROLLED_OUT(Error, std::cerr)
                << "MACE::SimulationG4::MPIExecutive::Execute: Command \"" << command << "\" failed (G4UIcommandStatus: " << commandStatus << ')' << std::endl;
            break;
        }
    }
}

} // namespace MACE::SimulationG4
