/// @file Read/write the current geometry description configuration from/to a yaml.
/// @attention If a new geometry description class is added, it needs to be added to
/// the std::tuple in the source file. Otherwise it wouldn't be covered.
/// @author Shi-Han Zhao

#include "Core/Geometry/Description/All.hxx"
#include "Core/Geometry/DescriptionIO.hxx"
#include "Utility/ObserverPtr.hxx"
#include "Utility/TupleForEach.hxx"

#include "yaml-cpp/yaml.h"

#include <fstream>
#include <tuple>

namespace MACE::Core::Geometry::DescriptionIO {

using Utility::ObserverPtr;
using Utility::TupleForEach;
using namespace Description;

/// @brief A std::tuple holding pointers to all geometry descriptions that will be read and written.
/// @attention If there is a new geometry description class, add to this.
static std::tuple<ObserverPtr<AcceleratorField>,
                  ObserverPtr<EMCal>,
                  ObserverPtr<EMCalField>,
                  ObserverPtr<EMCalShield>,
                  ObserverPtr<CDC>,
                  ObserverPtr<Collimator>,
                  ObserverPtr<SelectorField>,
                  ObserverPtr<SpectrometerField>,
                  ObserverPtr<SpectrometerMagnet>,
                  ObserverPtr<SpectrometerShield>,
                  ObserverPtr<Target>,
                  ObserverPtr<TransportLine>,
                  ObserverPtr<MCP>,
                  ObserverPtr<World>>
    descriptionTuple;

static void InitializeDescriptionTuple() {
    auto GetDescriptionInstance = []<IsDescription T>(ObserverPtr<T>& descriptionPtr) {
        descriptionPtr = std::addressof(T::Instance());
    };
    TupleForEach(descriptionTuple, GetDescriptionInstance);
}

void Read(const std::string& yamlFileName) {
    InitializeDescriptionTuple();
    const auto geomYaml = YAML::LoadFile(yamlFileName);
    auto ReadDescription = [&geomYaml]<IsDescription T>(ObserverPtr<T> descriptionPtr) {
        descriptionPtr->Read(geomYaml);
    };
    TupleForEach(std::as_const(descriptionTuple), ReadDescription);
}

void Write(const std::string& yamlFileName) {
    InitializeDescriptionTuple();
    YAML::Node geomYaml;
    auto WriteDescription = [&geomYaml]<IsDescription T>(ObserverPtr<const T> descriptionPtr) {
        descriptionPtr->Write(geomYaml);
    };
    TupleForEach(std::as_const(descriptionTuple), WriteDescription);
    std::ofstream yamlOut(yamlFileName, std::ios::out);
    yamlOut << geomYaml;
}

} // namespace MACE::Core::Geometry::DescriptionIO
