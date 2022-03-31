#include "Core/Geometry/Description/All.hxx"
#include "Core/Geometry/DescriptionIO.hxx"
#include "Utility/ObserverPtr.hxx"

#include "yaml-cpp/yaml.h"

#include <tuple>

namespace MACE::Core::Geometry::DescriptionIO {

using Utility::ObserverPtr;
using namespace Description;

static std::tuple<ObserverPtr<AcceleratorField>,
                  ObserverPtr<Calorimeter>,
                  ObserverPtr<CalorimeterField>,
                  ObserverPtr<CalorimeterShield>,
                  ObserverPtr<Collimator>,
                  ObserverPtr<FirstBendField>,
                  ObserverPtr<FirstBendSolenoid>,
                  ObserverPtr<FirstTransportField>,
                  ObserverPtr<FirstTransportSolenoid>,
                  ObserverPtr<SecondBendField>,
                  ObserverPtr<SecondBendSolenoid>,
                  ObserverPtr<SecondTransportField>,
                  ObserverPtr<SecondTransportSolenoid>,
                  ObserverPtr<SelectorField>,
                  ObserverPtr<SpectrometerBody>,
                  ObserverPtr<SpectrometerCells>,
                  ObserverPtr<SpectrometerField>,
                  ObserverPtr<SpectrometerFieldWires>,
                  ObserverPtr<SpectrometerMagnet>,
                  ObserverPtr<SpectrometerReadoutLayers>,
                  ObserverPtr<SpectrometerSenseWires>,
                  ObserverPtr<SpectrometerSensitiveVolumes>,
                  ObserverPtr<SpectrometerShield>,
                  ObserverPtr<Target>,
                  ObserverPtr<ThirdTransportField>,
                  ObserverPtr<ThirdTransportSolenoid>,
                  ObserverPtr<VertexDetector>,
                  ObserverPtr<World>>
    descriptionTuple;

static void InitializeDescriptionTuple() {
    auto GetDescriptionInstance = []<IsDescription T>(ObserverPtr<T>& descriptionPtr) {
        descriptionPtr = std::addressof(T::Instance());
    };
    std::apply(GetDescriptionInstance, descriptionTuple);
}

bool Read(const std::string& yamlFile) {
    InitializeDescriptionTuple();
    const auto geomYaml = YAML::LoadFile(yamlFile);
    auto ReadDescription = [&geomYaml]<IsDescription T>(ObserverPtr<T> descriptionPtr) {
        descriptionPtr->Read(geomYaml);
    };
    std::apply(ReadDescription, std::as_const(descriptionTuple));
}

bool Write(const std::string& yamlFile) {
    InitializeDescriptionTuple();
    auto geomYaml = YAML::LoadFile(yamlFile);
    auto WriteDescription = [&geomYaml]<IsDescription T>(ObserverPtr<const T> descriptionPtr) {
        descriptionPtr->Write(geomYaml);
    };
    std::apply(WriteDescription, std::as_const(descriptionTuple));
}

} // namespace MACE::Core::Geometry::DescriptionIO
