#include "DataModel/SimHit/VertexDetectorSimHit.hxx"

using namespace MACE::DataModel;

DoubleBranchSocket       VertexDetectorSimHit::fgVertexTime("vtxT", 0);
Vector3FBranchSocket VertexDetectorSimHit::fgVertexPosition("vtxX", 0, 0, 0);
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
    fgVertexTime.CreateBranch(tree);
    fgVertexPosition.CreateBranch(tree);
    fgPDGCode.CreateBranch(tree);
    fgEventID.CreateBranch(tree);
    fgTrackID.CreateBranch(tree);
}

void VertexDetectorSimHit::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgVertexTime.ConnectToBranch(tree);
    fgVertexPosition.ConnectToBranch(tree);
    fgPDGCode.ConnectToBranch(tree);
    fgEventID.ConnectToBranch(tree);
    fgTrackID.ConnectToBranch(tree);
}
