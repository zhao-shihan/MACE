#include "MACE/DataModel/Hit/EMCHit.h++"

namespace MACE::DataModel {

template<>
EMCHit::Column::Time::BranchSocket EMCHit::Column::Time::Base::fgBranchSocket = 
    {"t", "Hitting Time", 0};
template<>
EMCHit::Column::EnergyDeposition::BranchSocket EMCHit::Column::EnergyDeposition::Base::fgBranchSocket = 
    {"E", "Energy Deposition", 0};

inline namespace Hit {

void EMCHit::CreateAllBranch(TTree& tree) {
    Column::Time::CreateBranch(tree);
    Column::EnergyDeposition::CreateBranch(tree);
}

void EMCHit::ConnectToAllBranch(TTree& tree) {
    Column::Time::ConnectToBranch(tree);
    Column::EnergyDeposition::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
