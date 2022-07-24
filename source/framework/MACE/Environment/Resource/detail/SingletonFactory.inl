namespace MACE::Environment::Memory::Detail {

template<class ASingleton>
void SingletonFactory::Instantiate() {
    const std::type_index typeIndex(typeid(ASingleton));

    if (ASingleton::SingletonFactoryTestInstanceNodePtrNotNull()) {
        throw std::logic_error(
            std::string("MACE::Environment::Memory::SingletonFactory::Instantiate(...): Instance node pointer handled by ")
                .append(typeIndex.name())
                .append(" is not null"));
    }

    if (const auto existedTypeNode = std::as_const(fSingletonTypeCollection).find(typeIndex);
        existedTypeNode == fSingletonTypeCollection.cend()) [[likely]] {
        // Usual case, when only one static instance pointer in memory, and not
        // trying to query the deleted instance.
        const auto instance = new ASingleton();
        ASingleton::SingletonFactorySetInstanceNode(fSingletonInstanceList.emplace_front(
            static_cast<ObserverPtr<void>>(instance), static_cast<ISingletonBase*>(instance)));
        fSingletonTypeCollection.emplace(typeIndex, fSingletonInstanceList.begin());
    } else {
        // Assuming users are friendly and careful enough that not passing
        // ASingleton that is not derived from the expected base class
        // MACE::Environment::Memory::Singleton<ASingleton> (say "singleton
        // base class" below)), as far as concerned, this branch covers
        // possible 2 unusual cases:
        //
        // 1. The instance is deleted, so the static pointer stored in
        // "singleton base class" became null. But someone is not careful
        // enough to prevent further call to Instance() of that. In this case
        // we can recognize it and throw an instance of std::logic_error.
        //
        // 2. (Not confirmed) Static members of "singleton base class" has many
        // instances in memory. This might happend when there is dynamic
        // libraries contains "singleton base class" while the executable also
        // contains "singleton base class", since (...)::Singleton<ASingleton>
        // is a class template. In this case, for the identical type
        // ASingleton, this function might be called many times for each
        // different instances of static members of "singleton base class".
        // Since the actual instances are stored in the dynamically constructed
        // this->fSingletonInstanceList, they are singlet for sure. We just
        // look up for the type and return the corresponding pointer value.
        auto& existedInstanceNode = *(existedTypeNode->second);
        auto& [objectPtr, basePtr] = existedInstanceNode;
        if (objectPtr == nullptr and basePtr == nullptr) {
            throw std::logic_error(
                std::string("MACE::Environment::Memory::SingletonFactory::Instantiate(...): The instance of ")
                    .append(typeIndex.name())
                    .append(" has been deleted"));
        } else if (objectPtr == nullptr or basePtr == nullptr) {
            throw std::logic_error(
                std::string("MACE::Environment::Memory::SingletonFactory::Instantiate(...): The instance node of ")
                    .append(typeIndex.name())
                    .append(" is corrupted (partially null)"));
        }
        ASingleton::SingletonFactorySetInstanceNode(existedInstanceNode);
    }
}

} // namespace MACE::Environment::Memory::Detail
