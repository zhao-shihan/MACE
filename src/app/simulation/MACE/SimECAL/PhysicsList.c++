#include "MACE/SimECAL/PhysicsList.h++"

#include "G4IonTable.hh"
#include "G4NuclideTable.hh"

namespace MACE::SimECAL {

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{this},
    StandardPhysicsListBase{} {}

auto PhysicsList::ConstructProcess() -> void {
    StandardPhysicsListBase::ConstructProcess();

    constexpr auto timeScale{1e12};

    const auto nuclideTable{G4NuclideTable::GetNuclideTable()};
    for (std::size_t i = 0; i < nuclideTable->entries(); i++) {
        const auto nuclide{nuclideTable->GetIsotopeByIndex(i)};
        nuclide->SetLifeTime(nuclide->GetLifeTime() / timeScale);
    }
}

} // namespace MACE::SimECAL
