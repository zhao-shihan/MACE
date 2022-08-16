namespace MACE::Environment::CLI::internal {

template<typename... Args>
argparse::Argument& CLIBase::AddArgument(Args&&... args) {
    if (not Parsed()) {
        return fArgParser.add_argument(std::forward<Args>(args)...);
    } else {
        ThrowParsed();
    }
}

} // namespace MACE::Environment::CLI::internal
