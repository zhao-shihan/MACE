#pragma once

#include "G4VHit.hh"

#include "SimG4/Global.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"

class MACE::SimG4::Hit::CalorimeterHit final :
    public G4VHit,
    public MACE::DataModel::Hit::CalorimeterHit {
public:
    CalorimeterHit() noexcept;
    CalorimeterHit(const CalorimeterHit& hit) noexcept;
    CalorimeterHit(CalorimeterHit&& hit) noexcept;
    ~CalorimeterHit() noexcept {}
    CalorimeterHit& operator=(const CalorimeterHit& hit) noexcept;
    CalorimeterHit& operator=(CalorimeterHit&& hit) noexcept;

    static void CreateBranches(TTree* tree);
    inline void FillBranches() noexcept;
    static void ReadBranches(TTree* tree);

    const auto& GetParticlePDGCode() const { return fPDGCode; }
    auto GetTrackID() const { return fTrackID; }

    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetTrackID(Int_t val) { fTrackID = val; }

private:
    Int_t fPDGCode;
    Int_t fTrackID;

    static DataModel::Column<Int_t> fgPDGCode;
    static DataModel::Column<Int_t> fgTrackID;

public:
    inline void* operator new(size_t);
    inline void  operator delete(void*);
};

void MACE::SimG4::Hit::CalorimeterHit::FillBranches() noexcept {
    DataModel::Hit::CalorimeterHit::FillBranches();
    fgPDGCode.value = fPDGCode;
    fgTrackID.value = fTrackID;
}

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

namespace MACE::SimG4::Hit {

    using CalorimeterHitCollection = G4THitsCollection<CalorimeterHit>;

    extern G4Allocator<CalorimeterHit>* CalorimeterHitAllocator;

    inline void* CalorimeterHit::operator new(size_t) {
        return static_cast<void*>(CalorimeterHitAllocator->MallocSingle());
    }

    inline void CalorimeterHit::operator delete(void* hit) {
        CalorimeterHitAllocator->FreeSingle(static_cast<CalorimeterHit*>(hit));
    }

}
