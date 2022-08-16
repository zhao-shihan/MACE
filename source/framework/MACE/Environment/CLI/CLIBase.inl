namespace MACE::Environment::CLI {

argparse::Argument& CLIBase::AddArgument(auto&&... args) {
    if (not Parsed()) {
        return fArgParser.add_argument(std::forward<decltype(args)>(args)...);
    } else {
        ThrowParsed();
    }
}

} // namespace MACE::Environment::CLI
