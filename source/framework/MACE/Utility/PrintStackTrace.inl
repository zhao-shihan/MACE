namespace MACE::Utility {

template<Concept::Character AChar>
void PrintStackTrace(backward::StackTrace& stack, std::basic_ostream<AChar>& os) {
    using namespace std::string_view_literals;

    backward::TraceResolver resolver;
    resolver.load_stacktrace(stack);

    const auto oldFlag = os.flags();
    const auto oldFill = os.fill();
    os << "Stack trace (most recent call last):\n"sv;
    backward::SnippetFactory snippetFactory;
    for (int frame = static_cast<int>(stack.size()) - 1; frame >= 0; --frame) {
        const auto trace = resolver.resolve(stack[frame]);
        const std::string_view function = trace.object_function;
        const std::string_view binary = trace.object_filename;
        const auto& source = trace.source;
        os << '#' << std::setw(2) << std::setfill(' ') << std::left << frame
           << ' ' << std::setw(sizeof(void*) * CHAR_BIT / 4 + 2) << std::setfill('0') << std::internal << trace.addr
           << " in "sv << (function.empty() ? "??"sv : function)
           << " from "sv << (binary.empty() ? "??"sv : binary);
        if (not source.filename.empty()) {
            os << " at "sv << source.filename << ':' << source.line;
            if (source.col > 0) { os << ':' << source.col; }
            if (const auto snippet = snippetFactory.get_snippet(source.filename, source.line, 1);
                not snippet.empty()) {
                auto&& [line, content] = snippet.front();
                os << "\n    "sv << std::setw(Math::GetDigits<10>(line)) << std::setfill(' ') << std::right << line << " |"sv << content;
            }
        }
        os << '\n';
    }
    os << std::flush
       << std::setfill(oldFill)
       << std::setiosflags(oldFlag);
}

} // namespace MACE::Utility
