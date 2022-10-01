namespace MACE::Env::Memory::internal {

template<Singletonized ASingleton>
[[nodiscard]] SingletonPool::Node& SingletonFactory::InstantiateOrFind() {
    auto& instancePool = SingletonPool::Instance();
    if (const auto existedNode = instancePool.Find<ASingleton>();
        not existedNode.has_value()) [[likely]] {
        return instancePool.Insert(new ASingleton());
    } else {
        return existedNode.value();
    }
    // About the above "if" statement:
    //
    // True:
    //   Usual case, when only one static instance pointer in memory, and not
    //   trying to query the deleted instance.
    //
    // False:
    //   Assuming users are friendly and careful enough that not passing
    //   ASingleton that is not derived from the expected base class
    //   MACE::Env::Memory::Singleton<ASingleton> (say "singleton
    //   base class" below)), as far as concerned, this branch covers
    //   possible 2 unusual cases:
    //
    //   1. The instance is deleted, so the static pointer stored in
    //   "singleton base class" became null. But someone is not careful
    //   enough to prevent further call to Instance() of that. In this case
    //   we can recognize it and throw an instance of std::logic_error.
    //
    //   2. (Not confirmed) Static members of "singleton base class" has many
    //   instances in memory. This might happend when there is dynamic
    //   libraries contains "singleton base class" while the executable also
    //   contains "singleton base class", since (...)::Singleton<ASingleton>
    //   is a class template. In this case, for the identical type
    //   ASingleton, this function might be called many times for each
    //   different instances of static members of "singleton base class".
    //   Since the actual instances are stored in the dynamically constructed
    //   this->fSingletonInstanceList, they are singlet for sure. We just
    //   look up for the type and return the corresponding pointer value.
}

} // namespace MACE::Env::Memory::internal
