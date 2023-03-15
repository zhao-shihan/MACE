#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Extension::Geant4X::Generator {

class SurfaceMuon;

class SurfaceMuonMessenger final : public Env::Memory::Singleton<SurfaceMuonMessenger>,
                                   public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    SurfaceMuonMessenger();
    ~SurfaceMuonMessenger();

public:
    void AssignTo(gsl::not_null<SurfaceMuon*> gen) { fSurfaceMuonGenerator = gen; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    SurfaceMuon* fSurfaceMuonGenerator;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMomentum;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMomentumRMS;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fPositionRMS;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fPositionZ;
};

} // namespace MACE::inline Extension::Geant4X::Generator
