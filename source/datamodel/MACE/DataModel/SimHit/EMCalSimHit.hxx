#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Hit/EMCalHit.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace SimHit {

using namespace std::string_view_literals;

class EMCalSimHit : public EMCalHit {
public:
    struct Entry : EMCalHit::Entry {
        using G4EventID = IntEntry<EMCalSimHit, 2, int>;
        using G4TrackID = IntEntry<EMCalSimHit, 3, int>;
        using PDGCode = IntEntry<EMCalSimHit, 4, int>;
    };

public:
    virtual ~EMCalSimHit() = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& PDGCode() const { return fPDGCode; }

    void G4EventID(auto&& v) { fG4EventID.Value(std::forward<decltype(v)>(v)); }
    void G4TrackID(auto&& v) { fG4TrackID.Value(std::forward<decltype(v)>(v)); }
    void PDGCode(auto&& v) { fPDGCode.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "EMCalSimHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::G4EventID fG4EventID;
    Entry::G4TrackID fG4TrackID;
    Entry::PDGCode fPDGCode;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace SimHit

template<>
EMCalSimHit::Entry::G4EventID::BranchSocket EMCalSimHit::Entry::G4EventID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::G4TrackID::BranchSocket EMCalSimHit::Entry::G4TrackID::Base::fgBranchSocket;
template<>
EMCalSimHit::Entry::PDGCode::BranchSocket EMCalSimHit::Entry::PDGCode::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
