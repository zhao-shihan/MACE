#include "DataModel/Vertex/MuoniumVertex.hxx"

using namespace MACE::DataModel;

ShortStringBranchSocket     MuoniumVertex::fgParticleName("particle", "");
DoubleBranchSocket         MuoniumVertex::fgVertexTimeCDC("vtxTimeCDC", 0);
Vector3FBranchSocket   MuoniumVertex::fgVertexPositionCDC("vtxPosCDC", { "x", "y", "z" }, { 0, 0, 0 });
DoubleBranchSocket         MuoniumVertex::fgVertexTimeMCP("vtxTimeMCP", 0);
Vector3FBranchSocket   MuoniumVertex::fgVertexPositionMCP("vtxPosMCP", { "x", "y", "z" }, { 0, 0, 0 });

MuoniumVertex::MuoniumVertex() noexcept :
    Base(),
    fParticleName(fgParticleName.GetValue()),
    fVertexTimeCDC(fgVertexTimeCDC.GetValue()),
    fVertexPositionCDC(fgVertexPositionCDC.GetValue()),
    fVertexTimeMCP(fgVertexTimeMCP.GetValue()),
    fVertexPositionMCP(fgVertexPositionMCP.GetValue()) {}

void MuoniumVertex::CreateBranches(TTree& tree) {
    Base::CreateBranches(tree);
    fgParticleName.CreateBranch(tree);
    fgVertexTimeCDC.CreateBranch(tree);
    fgVertexPositionCDC.CreateBranch(tree);
    fgVertexTimeMCP.CreateBranch(tree);
    fgVertexPositionMCP.CreateBranch(tree);
}

void MuoniumVertex::ConnectToBranches(TTree& tree) {
    Base::ConnectToBranches(tree);
    fgParticleName.ConnectToBranch(tree);
    fgVertexTimeCDC.ConnectToBranch(tree);
    fgVertexPositionCDC.ConnectToBranch(tree);
    fgVertexTimeMCP.ConnectToBranch(tree);
    fgVertexPositionMCP.ConnectToBranch(tree);
}
