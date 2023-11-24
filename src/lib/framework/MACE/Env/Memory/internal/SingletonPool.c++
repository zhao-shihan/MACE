#include "MACE/Env/Memory/internal/SingletonPool.h++"

#include <algorithm>

namespace MACE::Env::Memory::internal {

[[nodiscard]] auto SingletonPool::GetUndeletedInReverseInsertionOrder() const -> std::vector<BaseNode> {
    std::vector<std::pair<gsl::index, BaseNode>> undeletedListWithID;
    undeletedListWithID.reserve(fInstanceMap.size());
    for (auto&& [_, nodePair] : fInstanceMap) {
        const auto& [node, baseNodePair] = nodePair;
        if (node != nullptr) {
            undeletedListWithID.emplace_back(baseNodePair);
        }
    }

    std::ranges::sort(undeletedListWithID,
                      [](const auto& lhs, const auto& rhs) {
                          return lhs.first > rhs.first;
                      });

    std::vector<BaseNode> undeletedList;
    undeletedList.reserve(undeletedListWithID.size());
    for (auto&& [id, baseNode] : std::as_const(undeletedListWithID)) {
        undeletedList.emplace_back(baseNode);
    }
    return undeletedList;
}

} // namespace MACE::Env::Memory::internal
