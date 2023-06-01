#include "MACE/Env/Memory/internal/SingletonBase.h++"
#include "MACE/Env/Memory/internal/SingletonDeleter.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"

namespace MACE::Env::Memory::internal {

SingletonDeleter::~SingletonDeleter() {
    const auto instancesToBeDeleted = SingletonPool::Instance().GetUndeletedInReverseInsertionOrder();
    for (auto&& singletonBase : instancesToBeDeleted) {
        delete singletonBase;
    }
}

} // namespace MACE::Env::Memory::internal
