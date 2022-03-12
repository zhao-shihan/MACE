#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket            SpectrometerSimHit::fgEnergy("hitE", 0);
Vector3FBranchSocket       SpectrometerSimHit::fgMomentum("hitP", 0, 0, 0);
DoubleBranchSocket       SpectrometerSimHit::fgVertexTime("vtxT", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexPosition("vtxX", 0, 0, 0);
FloatBranchSocket      SpectrometerSimHit::fgVertexEnergy("vtxE", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexMomentum("vtxP", 0, 0, 0);
IntBranchSocket             SpectrometerSimHit::fgPDGCode("pdgCode", std::numeric_limits<Int_t>::max());
IntBranchSocket             SpectrometerSimHit::fgEventID("evtID", -1);
IntBranchSocket             SpectrometerSimHit::fgTrackID("trkID", -1);

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    Base(),
    fEnergy(fgEnergy.Value()),
    fMomentum(fgMomentum.Value()),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fVertexEnergy(fgVertexEnergy.Value()),
    fVertexMomentum(fgVertexMomentum.Value()),
    fPDGCode(fgPDGCode.Value()),
    fEventID(fgEventID.Value()),
    fTrackID(fgTrackID.Value()) {}

void SpectrometerSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgEnergy.CreateBranch(tree);
    fgMomentum.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgVertexEnergy.CreateBranch(tree);
    fgVertexMomentum.CreateBranch(tree);
    fgPDGCode.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgEnergy.ConnectToBranch(tree);
    fgMomentum.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgVertexEnergy.ConnectToBranch(tree);
    fgVertexMomentum.ConnectToBranch(tree);
    fgPDGCode.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
