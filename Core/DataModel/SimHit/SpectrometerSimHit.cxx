#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

Vector3FBranchSocket       SpectrometerSimHit::fgMomentum("mom", 0, 0, 0);
DoubleBranchSocket       SpectrometerSimHit::fgVertexTime("vtxT", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexPosition("vtx", 0, 0, 0);
IntBranchSocket             SpectrometerSimHit::fgPDGCode("pdgCode", std::numeric_limits<Int_t>::max());
IntBranchSocket             SpectrometerSimHit::fgEventID("evtID", -1);
IntBranchSocket             SpectrometerSimHit::fgTrackID("trkID", -1);

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    Base(),
    fMomentum(fgMomentum.Value()),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fPDGCode(fgPDGCode.Value()),
    fEventID(fgEventID.Value()),
    fTrackID(fgTrackID.Value()) {}

void SpectrometerSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgMomentum.CreateBranch(tree);
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgPDGCode.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgMomentum.ConnectToBranch(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgPDGCode.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
