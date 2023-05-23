#include "MACE/DataModel/Hit/EMCalHit.hxx"

namespace MACE::DataModel {

template<>
EMCalHit::Entry::Time::BranchSocket EMCalHit::Entry::Time::Base::fgBranchSocket = 
    {"t", "Hitting Time", 0};
template<>
EMCalHit::Entry::EnergyDeposition::BranchSocket EMCalHit::Entry::EnergyDeposition::Base::fgBranchSocket = 
    {"E", "Energy Deposition", 0};

inline namespace Hit {

void EMCalHit::CreateAllBranch(TTree& tree) {
    Entry::Time::CreateBranch(tree);
    Entry::EnergyDeposition::CreateBranch(tree);
}

void EMCalHit::ConnectToAllBranch(TTree& tree) {
    Entry::Time::ConnectToBranch(tree);
    Entry::EnergyDeposition::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
