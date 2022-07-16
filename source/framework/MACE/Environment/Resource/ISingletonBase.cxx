#include "MACE/Environment/Resource/ISingletonBase.hxx"

namespace MACE::Environment::Resource {

ISingletonBase::ISingletonBase() :
    fInstanceBaseNodePtr(nullptr) {}

ISingletonBase::~ISingletonBase() {
    *fInstanceBaseNodePtr = nullptr;
}

} // namespace MACE::Environment::Resource
