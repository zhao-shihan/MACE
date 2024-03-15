namespace MACE::Env::CLI {

auto CLIBase::AddArgument(auto&&... args) -> argparse::Argument& {
    if (not Parsed()) {
        return fArgParser.add_argument(std::forward<decltype(args)>(args)...);
    } else {
        ThrowParsed();
    }
}

} // namespace MACE::Env::CLI
