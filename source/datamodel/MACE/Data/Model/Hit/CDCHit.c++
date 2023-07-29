/* #include "MACE/Data/IO/Reader.h++"
#include "MACE/Data/IO/Writer.h++"
#include "MACE/Data/Model/Hit/CDCHit.h++"

namespace MACE::Data::inline IO::internal {

TTree t;
ReaderWriterBase<CDCHit, TTree> a = t;

} // namespace MACE::Data::inline IO::internal

namespace MACE::Data::inline Model {

inline namespace Field {

MACE_DATA_MODEL_FIELD_DEFINE_FIELD_NAME_TITLE(CDCHit::CellID, "cellID", "Hitting Cell ID")

} // namespace Field

} // namespace MACE::Data::inline Model
 */