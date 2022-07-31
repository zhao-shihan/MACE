#include "MACE/Environment/Memory/detail/ISingletonBase.hxx"
#include "MACE/Environment/Memory/detail/SingletonFactory.hxx"

namespace MACE::Environment::Memory::Detail {

SingletonFactory::~SingletonFactory() {
    for (auto&& singletonBase : fInstancePool.GetUndeletedInReverseInsertionOrder()) {
        delete singletonBase;
    }
}

} // namespace MACE::Environment::Memory::Detail
