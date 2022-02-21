#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SecondTransportField final :
    public MACE::Geometry::Interface::Entity {
public:
    SecondTransportField() = default;
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
