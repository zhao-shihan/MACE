namespace MACE::Env {

template<char L, typename... Ts>
auto Print(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::print(std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::println(std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::print(f, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::println(f, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::print(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::println(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::wostream& os, fmt::basic_format_string<wchar_t, fmt::type_identity_t<Ts>...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::print(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::wostream& os, fmt::basic_format_string<wchar_t, fmt::type_identity_t<Ts>...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) { return; }
    fmt::println(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<typename... Ts>
auto PrintWarning(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    Print<'W'>(stderr, std::move(fmt), std::forward<Ts>(args)...);
}

template<typename... Ts>
auto PrintLnWarning(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    PrintLn<'W'>(stderr, std::move(fmt), std::forward<Ts>(args)...);
}

template<typename... Ts>
auto PrintError(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    Print<'E'>(stderr, std::move(fmt), std::forward<Ts>(args)...);
}

template<typename... Ts>
auto PrintLnError(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    PrintLn<'E'>(stderr, std::move(fmt), std::forward<Ts>(args)...);
}

} // namespace MACE::Env
