namespace MACE::Environment::CLI::Detail {

template<typename... Args>
argparse::Argument& CLIBase::AddArgument(Args&&... args) {
    if (not Parsed()) {
        return fArgParser.add_argument(std::forward<Args>(args)...);
    } else {
        ThrowParsed();
    }
}

} // namespace MACE::Environment::CLI::Detail
