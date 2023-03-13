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

class IEntity;

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

    std::shared_ptr<Geometry::IEntity> fCollimator;
    std::shared_ptr<Geometry::IEntity> fEMCalField;
    std::shared_ptr<Geometry::IEntity> fEMCalShield;
    std::shared_ptr<Geometry::IEntity> fFirstBendField;
    std::shared_ptr<Geometry::IEntity> fFirstBendSolenoid;
    std::shared_ptr<Geometry::IEntity> fFirstTransportField;
    std::shared_ptr<Geometry::IEntity> fFirstTransportSolenoid;
    std::shared_ptr<Geometry::IEntity> fLinacField;
    std::shared_ptr<Geometry::IEntity> fMCP;
    std::shared_ptr<Geometry::IEntity> fSecondBendField;
    std::shared_ptr<Geometry::IEntity> fSecondBendSolenoid;
    std::shared_ptr<Geometry::IEntity> fSecondTransportField;
    std::shared_ptr<Geometry::IEntity> fSecondTransportSolenoid;
    std::shared_ptr<Geometry::IEntity> fSelectorField;
    std::shared_ptr<Geometry::IEntity> fSpectrometerField;
    std::shared_ptr<Geometry::IEntity> fSpectrometerMagnet;
    std::shared_ptr<Geometry::IEntity> fSpectrometerShield;
    std::shared_ptr<Geometry::IEntity> fThirdTransportField;
    std::shared_ptr<Geometry::IEntity> fThirdTransportSolenoid;
    std::shared_ptr<Geometry::IEntity> fWorld;
};

} // namespace SimTarget::Action

} // namespace MACE
