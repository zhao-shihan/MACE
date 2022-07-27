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
    for (auto&& command : commandList) {
        if (fG4UIManager->ApplyCommand(command) != 0) [[unlikely]] { break; }
    }
}

} // namespace MACE::SimulationG4
