namespace MACE::Geometry::Interface::__Meta {
    namespace __Impl {
        // implementation of initialize helper for fDescriptions
        template<size_t N, class Tuple>
        struct InitializeDescriptions {
            static void Initialize(Tuple& descriptions) {
                Initialize<N - 1>(descriptions);
                std::get<N - 1>(descriptions) = std::remove_const_t<std::remove_pointer_t<std::tuple_element_t<N - 1, Tuple>>>::Instance();
            }
        };
        template<class Tuple>
        struct InitializeDescriptions<1, Tuple> {
            static void Initialize(Tuple& descriptions) {
                std::get<0>(descriptions) = std::remove_const_t<std::remove_pointer_t<std::tuple_element_t<0, Tuple>>>::Instance();
            }
        };
    }
    // initialize helper for fDescriptions
    template<class Tuple>
    void InitializeDescriptions(Tuple& descriptions) {
        __Impl::InitializeDescriptions<std::tuple_size_v<Tuple>, Tuple>::Initialize(descriptions);
    }
}

template<class VolumeType, class... RequiredDescriptions>
MACE::Geometry::Interface::EntityWithDescription<VolumeType, RequiredDescriptions...>::EntityWithDescription() :
    Entity<VolumeType>(),
    fDescriptions() {
    // initialize fDescriptions
    __Meta::InitializeDescriptions(fDescriptions);
}

template<class VolumeType, class... RequiredDescriptions>
MACE::Geometry::Interface::EntityWithDescription<VolumeType, RequiredDescriptions...>::~EntityWithDescription() {}
