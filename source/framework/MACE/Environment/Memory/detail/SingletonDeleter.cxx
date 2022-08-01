#include "MACE/Environment/Memory/detail/ISingletonBase.hxx"
#include "MACE/Environment/Memory/detail/SingletonDeleter.hxx"
#include "MACE/Environment/Memory/detail/SingletonPool.hxx"

namespace MACE::Environment::Memory::Detail {

SingletonDeleter::~SingletonDeleter() {
    for (auto&& singletonBase : SingletonPool::Instance().GetUndeletedInReverseInsertionOrder()) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::Detail
