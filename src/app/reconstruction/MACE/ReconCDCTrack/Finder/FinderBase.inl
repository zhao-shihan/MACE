namespace MACE::ReconCDCTrack::inline Finder {

template<std::derived_from<DataModel::CDCHit> AHit,
         std::derived_from<DataModel::CDCPhysicsTrack> ATrack>
constexpr FinderBase<AHit, ATrack>::FinderBase(Env::VerboseLevel verboseLevel) :
    fVerboseLevel(verboseLevel) {}

template<std::derived_from<DataModel::CDCHit> AHit,
         std::derived_from<DataModel::CDCPhysicsTrack> ATrack>
template<std::derived_from<AHit> AReturnedHit,
         std::derived_from<ATrack> AReturnedTrack>
constexpr typename FinderBase<AHit, ATrack>::template FinderResult<AReturnedHit, AReturnedTrack> FinderBase<AHit, ATrack>::Find() {
    
}

} // namespace MACE::ReconCDCTrack::inline Finder
