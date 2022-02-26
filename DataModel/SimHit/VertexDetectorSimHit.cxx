#include "DataModel/SimHit/VertexDetectorSimHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket        VertexDetectorSimHit::fgVertexTime("VertexT", 0);
Vector3FBranchSocket VertexDetectorSimHit::fgVertexPosition("VertexPos", 0, 0, 0);
IntBranchSocket             VertexDetectorSimHit::fgPDGCode("PDGCode", std::numeric_limits<Int_t>::max());
IntBranchSocket             VertexDetectorSimHit::fgTrackID("TrackID", -1);

VertexDetectorSimHit::VertexDetectorSimHit() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fPDGCode(fgPDGCode.Value()),
    fTrackID(fgTrackID.Value()) {}

void VertexDetectorSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    tree.Branch(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.Branch(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void VertexDetectorSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.SetBranchAddress(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
