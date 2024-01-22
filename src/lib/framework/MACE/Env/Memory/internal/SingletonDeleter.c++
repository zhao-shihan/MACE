#include "MACE/Env/Memory/internal/SingletonBase.h++"
#include "MACE/Env/Memory/internal/SingletonDeleter.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"

namespace MACE::Env::Memory::internal {

SingletonDeleter::~SingletonDeleter() {
    for (auto&& singletonBase : SingletonPool::Instance().GetUndeletedInReverseInsertionOrder()) {
        delete singletonBase;
    }
}

} // namespace MACE::Env::Memory::internal
