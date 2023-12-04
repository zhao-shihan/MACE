#pragma once

#include "MACE/Compatibility/std2b/forward_like.h++"
#include "MACE/Data/Tuple.h++"
#include "MACE/Data/TupleModel.h++"
#include "MACE/Data/internal/BranchHelper.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "TLeaf.h"
#include "TTree.h"

#include "fmt/format.h"

#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <ranges>
#include <string>
#include <type_traits>

namespace MACE::Data {

template<TupleModelizable... Ts>
class Output : public NonMoveableBase {
public:
    using Model = TupleModel<Ts...>;

public:
    explicit Output(const std::string& name, const std::string& title = {});

    template<typename T = Tuple<Ts...>>
        requires std::assignable_from<Tuple<Ts...>&, T>
    auto Fill(T&& tuple) -> std::size_t;
    template<typename T = Tuple<Ts...>>
        requires std::assignable_from<Tuple<Ts...>&, T>
    auto operator<<(T&& tuple) -> const auto& { return (Fill(std::forward<T>(tuple)), *this); }

    template<std::ranges::input_range R = std::initializer_list<Tuple<Ts...>>>
        requires std::assignable_from<Tuple<Ts...>&, std::ranges::range_reference_t<R>>
    auto Fill(R&& data) -> std::size_t;
    template<std::ranges::input_range R = std::initializer_list<Tuple<Ts...>>>
        requires std::assignable_from<Tuple<Ts...>&, std::ranges::range_reference_t<R>>
    auto operator<<(R&& data) -> const auto& { return (Fill(std::forward<R>(data)), *this); }

    template<std::ranges::input_range R>
        requires std::indirectly_readable<std::ranges::range_value_t<R>> and
                 std::assignable_from<Tuple<Ts...>&, std::iter_reference_t<std::ranges::range_value_t<R>>>
    auto Fill(const R& data) -> std::size_t;
    template<std::ranges::input_range R>
        requires std::indirectly_readable<std::ranges::range_value_t<R>> and
                 std::assignable_from<Tuple<Ts...>&, std::iter_reference_t<std::ranges::range_value_t<R>>>
    auto operator<<(const R& data) -> const auto& { return (Fill(data), *this); }

    auto Entry() -> auto { return OutputIterator{this}; }

    auto Write(int option = 0, int bufferSize = 0) const -> auto { return fTree.Write(nullptr, option, bufferSize); }

private:
    class OutputIterator final {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = void;
        using pointer = void;
        using reference = void;
        using iterator_category = std::output_iterator_tag;

    public:
        explicit OutputIterator(Output* output);

        template<typename T = Tuple<Ts...>>
        auto operator=(T&& data) const -> auto& { return (*fOutput << std::forward<T>(data), *this); }

        auto operator*() const -> auto& { return *this; }
        auto operator++() const -> auto& { return *this; }
        auto operator++(int) const -> auto& { return *this; }

    private:
        Output* fOutput;
    };

private:
    TTree fTree;
    Tuple<Ts...> fEntry;

    internal::BranchHelper<Tuple<Ts...>> fBranchHelper;
};

} // namespace MACE::Data

#include "MACE/Data/Output.inl"
