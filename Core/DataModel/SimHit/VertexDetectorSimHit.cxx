#include "DataModel/SimHit/VertexDetectorSimHit.hxx"

using namespace MACE::DataModel;

FloatBranchSocket        VertexDetectorSimHit::fgVertexTime("vtxT", 0);
Vector3FBranchSocket VertexDetectorSimHit::fgVertexPosition("vtxPos", 0, 0, 0);
IntBranchSocket             VertexDetectorSimHit::fgPDGCode("pdgCode", std::numeric_limits<Int_t>::max());
IntBranchSocket             VertexDetectorSimHit::fgEventID("evtID", -1);
IntBranchSocket             VertexDetectorSimHit::fgTrackID("trkID", -1);

VertexDetectorSimHit::VertexDetectorSimHit() noexcept :
    Base(),
    fVertexTime(fgVertexTime.Value()),
    fVertexPosition(fgVertexPosition.Value()),
    fPDGCode(fgPDGCode.Value()),
    fEventID(fgEventID.Value()),
    fTrackID(fgTrackID.Value()) {}

void VertexDetectorSimHit::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    tree.Branch(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.Branch(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.Branch(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.Branch(fgEventID.BranchName(), fgEventID.Address());
    tree.Branch(fgTrackID.BranchName(), fgTrackID.Address());
}

void VertexDetectorSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    tree.SetBranchAddress(fgVertexTime.BranchName(), fgVertexTime.Address());
    tree.SetBranchAddress(fgVertexPosition.BranchName(), fgVertexPosition.Address());
    tree.SetBranchAddress(fgPDGCode.BranchName(), fgPDGCode.Address());
    tree.SetBranchAddress(fgEventID.BranchName(), fgEventID.Address());
    tree.SetBranchAddress(fgTrackID.BranchName(), fgTrackID.Address());
}
