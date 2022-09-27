namespace MACE::Utility {

template<Concept::Character AChar>
void PrintStackTrace(backward::StackTrace& stack, std::basic_ostream<AChar>& os) {
    using namespace std::string_view_literals;

    backward::TraceResolver resolver;
    resolver.load_stacktrace(stack);

    const auto prevFlag = os.flags();
    const auto prevFill = os.fill();
    os << "Stack trace (most recent call last):\n"sv;
    backward::ResolvedTrace trace;
    backward::SnippetFactory snippetFactory;
    for (int frame = static_cast<int>(stack.size()) - 1; frame >= 0; --frame) {
        trace = resolver.resolve(stack[frame]);
        const auto& function = trace.object_function;
        const auto& binary = trace.object_filename;
        const auto& source = trace.source;
        os << '#' << std::setw(2) << std::setfill(' ') << std::left << frame
           << ' ' << std::setw(sizeof(void*) * CHAR_BIT / 4 + 2) << std::setfill('0') << std::internal << trace.addr
           << " in "sv << (function.empty() ? "??"sv : function)
           << " from "sv << (binary.empty() ? "??"sv : binary);
        if (source.filename.empty()) {
            os << '\n';
        } else {
            constexpr unsigned int maxSnippetLines = 5;
            if (const auto snippet = snippetFactory.get_snippet(source.filename, source.line, maxSnippetLines);
                snippet.empty()) {
                os << " at "sv << source.filename << ':' << source.line << '\n';
            } else {
                os << "\n    at "sv << source.filename << ':' << source.line << '\n';
                const auto numberWidth = Math::GetDigits10(source.line + maxSnippetLines / 2);
                for (auto&& [line, content] : snippet) {
                    os << "    "sv << std::setw(numberWidth) << std::setfill(' ') << std::right << line << (line == source.line ? '>' : ' ') << '|' << content << '\n';
                }
            }
        }
    }
    os << std::flush
       << std::setfill(prevFill)
       << std::setiosflags(prevFlag);
}

} // namespace MACE::Utility
