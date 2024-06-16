#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include "envparse/parse.h++"

#include <string>

namespace MACE::Detector::Description {

class FieldOption final : public Mustard::Detector::Description::DescriptionBase<FieldOption> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    FieldOption();
    ~FieldOption() = default;

public:
    auto UseFast() const -> auto { return fUseFast; }
    auto FieldDataFileName() const -> auto { return envparse::parse(fFieldDataFileName); }
    auto RawFieldDataFileName() const -> const auto& { return fFieldDataFileName; }

    auto UseFast(bool val) -> void { fUseFast = val; }
    auto FieldDataFileName(std::string val) -> void { fFieldDataFileName = std::move(val); }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    bool fUseFast;
    std::string fFieldDataFileName;
};

} // namespace MACE::Detector::Description
