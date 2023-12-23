namespace MACE::Env::Memory {

template<typename ADerived>
void** Singleton<ADerived>::fgInstance{};

template<typename ADerived>
Singleton<ADerived>::Singleton() :
    SingletonBase{} {
    static_assert(Singletonified<ADerived>);
}

template<typename ADerived>
Singleton<ADerived>::~Singleton() {
    UpdateInstance();
    *fgInstance = nullptr;
}

template<typename ADerived>
MACE_ALWAYS_INLINE auto Singleton<ADerived>::Instance() -> ADerived& {
    switch (UpdateInstance()) {
    case Status::NotInstantiated: {
        auto& pool{internal::SingletonPool::Instance()};
        if (pool.Contains<ADerived>()) {
            throw std::logic_error{fmt::format("MACE::Env::Memory::Singleton: "
                                               "Trying to construct {} (environmental singleton) twice",
                                               typeid(ADerived).name())};
        }
        fgInstance = &pool.Insert<ADerived>(SingletonInstantiator::New<ADerived>());
    }
        [[fallthrough]];
    [[likely]] case Status::Available:
        return *static_cast<ADerived*>(*fgInstance);
    case Status::Expired:
        throw std::logic_error{fmt::format("MACE::Env::Memory::Singleton::Instance(): "
                                           "The instance of {} has been deleted",
                                           typeid(ADerived).name())};
    }
    std2b::unreachable();
}

template<typename ADerived>
MACE_ALWAYS_INLINE auto Singleton<ADerived>::Instantiated() -> bool {
    const auto status{UpdateInstance()};
    return status == Status::Available or
           status == Status::Expired;
}

template<typename ADerived>
MACE_ALWAYS_INLINE auto Singleton<ADerived>::UpdateInstance() -> Status {
    if (fgInstance == nullptr) [[unlikely]] {
        if (const auto optionalNode{internal::SingletonPool::Instance().Find<ADerived>()};
            optionalNode.has_value()) {
            fgInstance = &optionalNode->get();
        } else {
            return Status::NotInstantiated;
        }
    }
    if (*fgInstance == nullptr) {
        return Status::Expired;
    } else {
        return Status::Available;
    }
}

} // namespace MACE::Env::Memory
