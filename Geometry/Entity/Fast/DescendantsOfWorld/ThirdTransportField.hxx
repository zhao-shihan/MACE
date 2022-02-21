#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::ThirdTransportField final :
    public MACE::Geometry::Interface::Entity {
public:
    ThirdTransportField() = default;
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
