#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

Vector3FBranchSocket       SpectrometerSimHit::fgMomentum("mom", 0, 0, 0);
FloatBranchSocket        SpectrometerSimHit::fgVertexTime("vtxT", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexPosition("vtxPos", 0, 0, 0);
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
    tree.Branch(fgMomentum.BranchName(), fgMomentum.Address());
    tree.Branch(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.Branch(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgEventID.BranchName(), fgEventID.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgMomentum.BranchName(), fgMomentum.Address());
    tree.SetBranchAddress(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.SetBranchAddress(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgEventID.BranchName(), fgEventID.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
