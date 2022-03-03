#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::FirstTransportField final :
    public MACE::Geometry::Interface::Entity {
public:
    FirstTransportField() = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
