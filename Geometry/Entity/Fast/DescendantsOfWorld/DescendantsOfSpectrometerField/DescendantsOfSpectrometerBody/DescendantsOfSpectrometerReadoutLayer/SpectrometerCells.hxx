#pragma once

#include "G4TwoVector.hh"

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerCells final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerCells();
    ~SpectrometerCells() noexcept = default;
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

    [[nodiscard]] const auto& GetLayerIdAndPosition(G4int cellId) const { return fCellLayerIDAndPositionList[cellId]; }

private:
    void ConstructSelf(G4bool checkOverlaps) override;

private:
    std::vector<std::pair<G4int, G4TwoVector>> fCellLayerIDAndPositionList;
};
