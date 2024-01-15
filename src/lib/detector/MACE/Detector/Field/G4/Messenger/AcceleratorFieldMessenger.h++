#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class AcceleratorField;

inline namespace Messenger {

class AcceleratorFieldMessenger final : public Env::Memory::Singleton<AcceleratorFieldMessenger>,
                                        public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    AcceleratorFieldMessenger();
    ~AcceleratorFieldMessenger();

public:
    void AssignTo(gsl::not_null<AcceleratorField*> field) { fAcceleratorField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    AcceleratorField* fAcceleratorField;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fAcceleratorPotential;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
