#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector {

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

class GeometryBase;

} // namespace Detector

namespace SimTarget::Action {

class DetectorConstruction final : public Env::Memory::FreeSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using UsedDescriptions = std::tuple<Detector::Description::Collimator,
                                        Detector::Description::EMCalField,
                                        Detector::Description::EMCalShield,
                                        Detector::Description::LinacField,
                                        Detector::Description::MCP,
                                        Detector::Description::SelectorField,
                                        Detector::Description::SpectrometerField,
                                        Detector::Description::SpectrometerMagnet,
                                        Detector::Description::SpectrometerShield,
                                        Detector::Description::TransportLine,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::GeometryBase> fCollimator;
    std::shared_ptr<Detector::GeometryBase> fEMCalField;
    std::shared_ptr<Detector::GeometryBase> fEMCalShield;
    std::shared_ptr<Detector::GeometryBase> fFirstBendField;
    std::shared_ptr<Detector::GeometryBase> fFirstBendSolenoid;
    std::shared_ptr<Detector::GeometryBase> fFirstTransportField;
    std::shared_ptr<Detector::GeometryBase> fFirstTransportSolenoid;
    std::shared_ptr<Detector::GeometryBase> fLinacField;
    std::shared_ptr<Detector::GeometryBase> fMCP;
    std::shared_ptr<Detector::GeometryBase> fSecondBendField;
    std::shared_ptr<Detector::GeometryBase> fSecondBendSolenoid;
    std::shared_ptr<Detector::GeometryBase> fSecondTransportField;
    std::shared_ptr<Detector::GeometryBase> fSecondTransportSolenoid;
    std::shared_ptr<Detector::GeometryBase> fSelectorField;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerField;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerMagnet;
    std::shared_ptr<Detector::GeometryBase> fSpectrometerShield;
    std::shared_ptr<Detector::GeometryBase> fThirdTransportField;
    std::shared_ptr<Detector::GeometryBase> fThirdTransportSolenoid;
    std::shared_ptr<Detector::GeometryBase> fWorld;
};

} // namespace SimTarget::Action

} // namespace MACE
