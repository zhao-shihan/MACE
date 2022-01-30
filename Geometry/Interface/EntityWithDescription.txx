namespace MACE::Geometry::Interface::Meta__ {
    namespace Impl__ {
        // implementation of initialize helper for fDescriptions
        template<size_t N, class Tuple>
        struct InitializeDescriptions {
            static void Initialize(Tuple& descriptions) {
                InitializeDescriptions<N - 1, Tuple>::Initialize(descriptions);
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
        Impl__::InitializeDescriptions<std::tuple_size_v<Tuple>, Tuple>::Initialize(descriptions);
    }
}

template<class Volume_t, class... RequiredDescriptions>
MACE::Geometry::Interface::EntityWithDescription<Volume_t, RequiredDescriptions...>::EntityWithDescription() :
    Entity<Volume_t>(),
    fDescriptions() {
    // initialize fDescriptions
    Meta__::InitializeDescriptions(fDescriptions);
}

template<class Volume_t, class... RequiredDescriptions>
MACE::Geometry::Interface::EntityWithDescription<Volume_t, RequiredDescriptions...>::~EntityWithDescription() {}
