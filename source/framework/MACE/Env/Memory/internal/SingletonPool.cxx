#include "MACE/Env/Memory/internal/SingletonPool.hxx"

#include <algorithm>

namespace MACE::Env::Memory::internal {

[[nodiscard]] std::vector<SingletonPool::BaseNode> SingletonPool::GetUndeletedInReverseInsertionOrder() const {
    std::vector<std::pair<gsl::index, BaseNode>> undeletedListWithId;
    undeletedListWithId.reserve(fInstanceMap.size());
    for (auto&& [_, nodePair] : fInstanceMap) {
        const auto& [node, baseNodePair] = nodePair;
        if (node != nullptr) {
            undeletedListWithId.emplace_back(baseNodePair);
        }
    }

    std::ranges::sort(undeletedListWithId,
                      [](const auto& lhs, const auto& rhs) {
                          return lhs.first > rhs.first;
                      });

    std::vector<BaseNode> undeletedList;
    undeletedList.reserve(undeletedListWithId.size());
    for (auto&& [id, baseNode] : std::as_const(undeletedListWithId)) {
        undeletedList.emplace_back(baseNode);
    }
    return undeletedList;
}

} // namespace MACE::Env::Memory::internal
