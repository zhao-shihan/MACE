#pragma once

#include "MACE/Environment/Memory/Concept/FreeSingletonized.hxx"
#include "MACE/Environment/Memory/detail/FreeSingletonPool.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory {

using MACE::Utility::ObserverPtr;

template<class ADerived>
class FreeSingleton : public Utility::NonCopyableBase {
protected:
    FreeSingleton();
    ~FreeSingleton();

public:
    static ADerived& Instance();

private:
    static void FindInstance();

private:
    static ObserverPtr<Detail::FreeSingletonPool::Node> fgInstanceNode;
};

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/FreeSingleton.inl"
