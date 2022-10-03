#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Core::Geometry {

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

} // namespace Core::Geometry

namespace SimTarget::Action {

class DetectorConstruction final : public Env::Memory::FreeSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using UsedDescriptions = std::tuple<Core::Geometry::Description::Collimator,
                                        Core::Geometry::Description::EMCalField,
                                        Core::Geometry::Description::EMCalShield,
                                        Core::Geometry::Description::LinacField,
                                        Core::Geometry::Description::MCP,
                                        Core::Geometry::Description::SelectorField,
                                        Core::Geometry::Description::SpectrometerField,
                                        Core::Geometry::Description::SpectrometerMagnet,
                                        Core::Geometry::Description::SpectrometerShield,
                                        Core::Geometry::Description::TransportLine,
                                        Core::Geometry::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Core::Geometry::IEntity> fCollimator;
    std::shared_ptr<Core::Geometry::IEntity> fEMCalField;
    std::shared_ptr<Core::Geometry::IEntity> fEMCalShield;
    std::shared_ptr<Core::Geometry::IEntity> fFirstBendField;
    std::shared_ptr<Core::Geometry::IEntity> fFirstBendSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fFirstTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fFirstTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fLinacField;
    std::shared_ptr<Core::Geometry::IEntity> fMCP;
    std::shared_ptr<Core::Geometry::IEntity> fSecondBendField;
    std::shared_ptr<Core::Geometry::IEntity> fSecondBendSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fSecondTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fSecondTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fSelectorField;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerField;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerMagnet;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerShield;
    std::shared_ptr<Core::Geometry::IEntity> fThirdTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fThirdTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fWorld;
};

} // namespace SimTarget::Action

} // namespace MACE
