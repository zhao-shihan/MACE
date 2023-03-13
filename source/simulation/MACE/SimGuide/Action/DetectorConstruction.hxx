#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Geometry {

namespace Description {

class Collimator;
class EMCalField;
class EMCalShield;
class LinacField;
class MCP;
class SelectorField;
class SpectrometerField;
class SpectrometerMagnet;
class SpectrometerShield;
class TransportLine;
class World;

} // namespace Description

class EntityBase;

} // namespace Geometry

namespace SimTarget::Action {

class DetectorConstruction final : public Env::Memory::FreeSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using UsedDescriptions = std::tuple<Geometry::Description::Collimator,
                                        Geometry::Description::EMCalField,
                                        Geometry::Description::EMCalShield,
                                        Geometry::Description::LinacField,
                                        Geometry::Description::MCP,
                                        Geometry::Description::SelectorField,
                                        Geometry::Description::SpectrometerField,
                                        Geometry::Description::SpectrometerMagnet,
                                        Geometry::Description::SpectrometerShield,
                                        Geometry::Description::TransportLine,
                                        Geometry::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Geometry::EntityBase> fCollimator;
    std::shared_ptr<Geometry::EntityBase> fEMCalField;
    std::shared_ptr<Geometry::EntityBase> fEMCalShield;
    std::shared_ptr<Geometry::EntityBase> fFirstBendField;
    std::shared_ptr<Geometry::EntityBase> fFirstBendSolenoid;
    std::shared_ptr<Geometry::EntityBase> fFirstTransportField;
    std::shared_ptr<Geometry::EntityBase> fFirstTransportSolenoid;
    std::shared_ptr<Geometry::EntityBase> fLinacField;
    std::shared_ptr<Geometry::EntityBase> fMCP;
    std::shared_ptr<Geometry::EntityBase> fSecondBendField;
    std::shared_ptr<Geometry::EntityBase> fSecondBendSolenoid;
    std::shared_ptr<Geometry::EntityBase> fSecondTransportField;
    std::shared_ptr<Geometry::EntityBase> fSecondTransportSolenoid;
    std::shared_ptr<Geometry::EntityBase> fSelectorField;
    std::shared_ptr<Geometry::EntityBase> fSpectrometerField;
    std::shared_ptr<Geometry::EntityBase> fSpectrometerMagnet;
    std::shared_ptr<Geometry::EntityBase> fSpectrometerShield;
    std::shared_ptr<Geometry::EntityBase> fThirdTransportField;
    std::shared_ptr<Geometry::EntityBase> fThirdTransportSolenoid;
    std::shared_ptr<Geometry::EntityBase> fWorld;
};

} // namespace SimTarget::Action

} // namespace MACE
