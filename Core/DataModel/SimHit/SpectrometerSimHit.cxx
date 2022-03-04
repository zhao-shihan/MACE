#include "DataModel/SimHit/SpectrometerSimHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket        SpectrometerSimHit::fgVertexTime("VtxT", 0);
Vector3FBranchSocket SpectrometerSimHit::fgVertexPosition("VtxPos", 0, 0, 0);
IntBranchSocket             SpectrometerSimHit::fgPDGCode("PDGCode", std::numeric_limits<Int_t>::max());
IntBranchSocket             SpectrometerSimHit::fgTrackID("TrkID", -1);

SpectrometerSimHit::SpectrometerSimHit() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fPDGCode(fgPDGCode.Value()),
    fTrackID(fgTrackID.Value()) {}

void SpectrometerSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    tree.Branch(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.Branch(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void SpectrometerSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.SetBranchAddress(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
