#include "MACE/DataModel/SimHit/EMCalSimHit.hxx"

namespace MACE::DataModel {

template<>
EMCalSimHit::Entry::G4EventID::BranchSocket EMCalSimHit::Entry::G4EventID::Base::fgBranchSocket = {"g4EventID", -1};
template<>
EMCalSimHit::Entry::G4TrackID::BranchSocket EMCalSimHit::Entry::G4TrackID::Base::fgBranchSocket = {"g4TrackID", -1};
template<>
EMCalSimHit::Entry::Particle::BranchSocket EMCalSimHit::Entry::Particle::Base::fgBranchSocket = {"particle", ""};

inline namespace SimHit {

void EMCalSimHit::CreateBranches(TTree& tree) {
    EMCalHit::CreateBranches(tree);
    decltype(fG4EventID)::CreateBranch(tree);
    decltype(fG4TrackID)::CreateBranch(tree);
    decltype(fParticle)::CreateBranch(tree);
}

void EMCalSimHit::ConnectToBranches(TTree& tree) {
    EMCalHit::ConnectToBranches(tree);
    decltype(fG4EventID)::ConnectToBranch(tree);
    decltype(fG4TrackID)::ConnectToBranch(tree);
    decltype(fParticle)::ConnectToBranch(tree);
}

} // namespace SimHit

} // namespace MACE::DataModel
