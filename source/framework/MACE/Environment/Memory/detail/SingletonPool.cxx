#include "MACE/Environment/Memory/detail/SingletonPool.hxx"

namespace MACE::Environment::Memory::Detail {

[[nodiscard]] std::vector<SingletonPool::BaseNode> SingletonPool::GetUndeletedInReverseInsertionOrder() const {
    std::vector<std::pair<std::size_t, BaseNode>> undeletedListWithId;
    undeletedListWithId.reserve(fInstanceMap.size());
    for (auto&& [_, nodePair] : fInstanceMap) {
        const auto& [node, baseNodePair] = nodePair;
        if (node != nullptr) {
            undeletedListWithId.emplace_back(baseNodePair);
        }
    }
    const auto undeletedCount = undeletedListWithId.size();

    std::vector<BaseNode> undeletedList(undeletedCount);
    for (auto&& [id, baseNode] : std::as_const(undeletedListWithId)) {
        undeletedList[undeletedCount - id - 1] = baseNode;
    }
    return undeletedList;
}

} // namespace MACE::Environment::Memory::Detail
