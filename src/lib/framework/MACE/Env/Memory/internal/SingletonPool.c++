#include "MACE/Env/Memory/internal/SingletonPool.h++"

#include <algorithm>
#include <cassert>

namespace MACE::Env::Memory::internal {

SingletonPool::~SingletonPool() {
    for (auto&& [_, nodeInfo] : fInstanceMap) {
        const auto& [node, index, base]{nodeInfo};
        assert(*node == nullptr);
    }
}

[[nodiscard]] auto SingletonPool::GetUndeletedInReverseInsertionOrder() const -> std::vector<gsl::owner<const SingletonBase*>> {
    std::vector<std::pair<gsl::index, gsl::owner<const SingletonBase*>>> undeletedListWithID;
    undeletedListWithID.reserve(fInstanceMap.size());
    for (auto&& [_, nodeInfo] : fInstanceMap) {
        const auto& [node, index, base]{nodeInfo};
        if (*node != nullptr) {
            undeletedListWithID.emplace_back(index, base);
        }
    }

    std::ranges::sort(undeletedListWithID,
                      [](const auto& lhs, const auto& rhs) {
                          return lhs.first > rhs.first;
                      });

    std::vector<gsl::owner<const SingletonBase*>> undeletedList;
    undeletedList.reserve(undeletedListWithID.size());
    for (auto&& [id, baseNode] : std::as_const(undeletedListWithID)) {
        undeletedList.emplace_back(baseNode);
    }
    return undeletedList;
}

} // namespace MACE::Env::Memory::internal
