#include "MACE/Env/Memory/internal/SingletonBase.hxx"
#include "MACE/Env/Memory/internal/SingletonDeleter.hxx"
#include "MACE/Env/Memory/internal/SingletonPool.hxx"

namespace MACE::Env::Memory::internal {

SingletonDeleter::~SingletonDeleter() {
    const auto instancesToBeDeleted = SingletonPool::Instance().GetUndeletedInReverseInsertionOrder();
    for (auto&& singletonBase : instancesToBeDeleted) {
        delete singletonBase;
    }
}

} // namespace MACE::Env::Memory::internal
