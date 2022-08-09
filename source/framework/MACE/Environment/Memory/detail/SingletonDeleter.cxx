#include "MACE/Environment/Memory/detail/ISingletonBase.hxx"
#include "MACE/Environment/Memory/detail/SingletonDeleter.hxx"
#include "MACE/Environment/Memory/detail/SingletonPool.hxx"

namespace MACE::Environment::Memory::Detail {

SingletonDeleter::~SingletonDeleter() {
    const auto instancesToBeDeleted = SingletonPool::Instance().GetUndeletedInReverseInsertionOrder();
    for (auto&& singletonBase : instancesToBeDeleted) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::Detail
