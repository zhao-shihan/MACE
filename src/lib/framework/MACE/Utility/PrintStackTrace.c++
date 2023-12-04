#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/PrintStackTrace.h++"

#include "backward.hpp"

#include "fmt/format.h"

#include <climits>
#include <string>
#include <utility>

namespace MACE::inline Utility {

void PrintStackTrace(backward::StackTrace& stack, int skip, std::FILE* stream) {
    backward::TraceResolver resolver;
    resolver.load_stacktrace(stack);

    const auto& mpiEnv{Env::MPIEnv::Instance()};

    const auto lineHeader{mpiEnv.Initialized() ? fmt::format("Rank{}> ", mpiEnv.CommWorldRank()) : ""};
    auto text{lineHeader + "Stack trace (most recent call last):\n"};
    backward::SnippetFactory snippetFactory;
    for (auto i{std::ssize(stack) - 1 - skip}; i >= 0; --i) {
        auto trace{resolver.resolve(stack[i])};
        text += fmt::format("{}#{:<2} {} in {} from {}",
                            lineHeader, i, std::move(trace.addr),
                            trace.object_function.empty() ? "??" : std::move(trace.object_function),
                            trace.object_filename.empty() ? "??" : std::move(trace.object_filename));
        if (auto&& src{trace.source};
            not src.filename.empty()) {
            text += fmt::format(" at {}:{}", src.filename, src.line);
            if (src.col > 0) { text += fmt::format(":{}", src.col); }
            if (auto snippet{snippetFactory.get_snippet(src.filename, src.line, 1)};
                not snippet.empty()) {
                auto&& [line, content] = snippet.front();
                text += fmt::format("\n{} {:7} |{}", lineHeader, std::move(line), std::move(content));
            }
        }
        text += '\n';
    }

    fmt::print(stream, "{}", text);
}

} // namespace MACE::inline Utility
