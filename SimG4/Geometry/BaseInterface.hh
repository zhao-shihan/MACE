#pragma once

#include "G4PVPlacement.hh"

#include "SimG4/Global.hh"

#include "VolumeSet.hh"

class MACE::SimG4::Geometry::BaseInterface {
public:
    BaseInterface(size_t volumeCount);
    virtual ~BaseInterface();

    virtual void Create(G4Material* material, const BaseInterface* mother) = 0;

    auto* GetSolidVolume() const { return fVolumeSetList.front().GetSolidVolume(); }
    auto* GetLogicalVolume() const { return fVolumeSetList.front().GetLogicalVolume(); }
    auto* GetPhysicalVolume() const { return fVolumeSetList.front().GetPhysicalVolume(); }
    auto* GetSolidVolume(size_t i) const { return fVolumeSetList[i].GetSolidVolume(); }
    auto* GetLogicalVolume(size_t i) const { return fVolumeSetList[i].GetLogicalVolume(); }
    auto* GetPhysicalVolume(size_t i) const { return fVolumeSetList[i].GetPhysicalVolume(); }
    auto  GetVolumeSetCount() const { return fVolumeSetList.size(); }

protected:
    auto& GetVolumeSet() { return fVolumeSetList.front(); }
    auto& GetVolumeSet(size_t i) { return fVolumeSetList[i]; }
    void  ResizeVolumeSetList(size_t length) { fVolumeSetList.resize(length); }

private:
    std::vector<VolumeSet> fVolumeSetList;
};

namespace MACE::SimG4::Geometry {
    constexpr G4bool checkOverlaps = false;
}
