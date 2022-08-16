#include "MACE/Environment/Memory/internal/ISingletonBase.hxx"
#include "MACE/Environment/Memory/internal/SingletonDeleter.hxx"
#include "MACE/Environment/Memory/internal/SingletonPool.hxx"

namespace MACE::Environment::Memory::internal {

SingletonDeleter::~SingletonDeleter() {
    const auto instancesToBeDeleted = SingletonPool::Instance().GetUndeletedInReverseInsertionOrder();
    for (auto&& singletonBase : instancesToBeDeleted) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::internal
