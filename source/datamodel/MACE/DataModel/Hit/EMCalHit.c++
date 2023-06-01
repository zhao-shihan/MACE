#include "MACE/DataModel/Hit/EMCalHit.h++"

namespace MACE::DataModel {

template<>
EMCalHit::Column::Time::BranchSocket EMCalHit::Column::Time::Base::fgBranchSocket = 
    {"t", "Hitting Time", 0};
template<>
EMCalHit::Column::EnergyDeposition::BranchSocket EMCalHit::Column::EnergyDeposition::Base::fgBranchSocket = 
    {"E", "Energy Deposition", 0};

inline namespace Hit {

void EMCalHit::CreateAllBranch(TTree& tree) {
    Column::Time::CreateBranch(tree);
    Column::EnergyDeposition::CreateBranch(tree);
}

void EMCalHit::ConnectToAllBranch(TTree& tree) {
    Column::Time::ConnectToBranch(tree);
    Column::EnergyDeposition::ConnectToBranch(tree);
}

} // namespace Hit

} // namespace MACE::DataModel
