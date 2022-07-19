#include "MACE/Environment/Resource/detail/ISingletonBase.hxx"

namespace MACE::Environment::Resource::Detail {

ISingletonBase::ISingletonBase() :
    fInstanceBaseNodePtr(nullptr) {}

ISingletonBase::~ISingletonBase() {
    *fInstanceBaseNodePtr = nullptr;
}

} // namespace MACE::Environment::Resource::Detail
