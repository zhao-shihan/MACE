#pragma once

#include "Geometry/Global.hxx"
#include "Geometry/Interface/Entity.hxx"

template<class Volume_t, class... RequiredDescriptions>
class MACE::Geometry::Interface::EntityWithDescription :
    public MACE::Geometry::Interface::Entity<Volume_t> {
protected:
    EntityWithDescription();
    virtual ~EntityWithDescription() = 0;
    EntityWithDescription(const EntityWithDescription&) = delete;
    EntityWithDescription& operator=(const EntityWithDescription&) = delete;

private:
    using DescriptionTuple = std::tuple<const RequiredDescriptions*...>;

public:
    template<size_t Index = 0>
    const std::tuple_element_t<Index, DescriptionTuple>& GetDescription() const { return std::get<Index>(fDescriptions); }

private:
    DescriptionTuple fDescriptions;
};

#include "Geometry/Interface/EntityWithDescription.txx"
