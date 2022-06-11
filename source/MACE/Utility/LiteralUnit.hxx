#pragma once

#include "CLHEP/Units/SystemOfUnits.h"

#define MACE_UTILITY_LITERAL_UNIT(suffix, unit)                        \
    constexpr long double operator""##suffix(long double val) {        \
        return val * (unit);                                           \
    }                                                                  \
    constexpr long double operator""##suffix(unsigned long long val) { \
        return val * (unit);                                           \
    }

namespace MACE::Utility::LiteralUnit {

// Length [L] symbols
inline namespace Length {

MACE_UTILITY_LITERAL_UNIT(_nm, CLHEP::nm);
MACE_UTILITY_LITERAL_UNIT(_um, CLHEP::um);
MACE_UTILITY_LITERAL_UNIT(_mm, CLHEP::mm);
MACE_UTILITY_LITERAL_UNIT(_cm, CLHEP::cm);
MACE_UTILITY_LITERAL_UNIT(_m, CLHEP::m);
MACE_UTILITY_LITERAL_UNIT(_km, CLHEP::km);

MACE_UTILITY_LITERAL_UNIT(_pc, CLHEP::pc);

} // namespace Length

// Area [L^2] symbols
inline namespace Area {

MACE_UTILITY_LITERAL_UNIT(_mm2, CLHEP::mm2);
MACE_UTILITY_LITERAL_UNIT(_cm2, CLHEP::cm2);
MACE_UTILITY_LITERAL_UNIT(_m2, CLHEP::m2);
MACE_UTILITY_LITERAL_UNIT(_km2, CLHEP::km2);

} // namespace Area

// Volume [L^3] symbols
inline namespace Volume {

MACE_UTILITY_LITERAL_UNIT(_mm3, CLHEP::mm3);
MACE_UTILITY_LITERAL_UNIT(_cm3, CLHEP::cm3);
MACE_UTILITY_LITERAL_UNIT(_m3, CLHEP::m3);
MACE_UTILITY_LITERAL_UNIT(_km3, CLHEP::km3);

MACE_UTILITY_LITERAL_UNIT(_L, CLHEP::L);
MACE_UTILITY_LITERAL_UNIT(_dL, CLHEP::dL);
MACE_UTILITY_LITERAL_UNIT(_cL, CLHEP::cL);
MACE_UTILITY_LITERAL_UNIT(_mL, CLHEP::mL);

} // namespace Volume

// Angle symbols
inline namespace Angle {

MACE_UTILITY_LITERAL_UNIT(_rad, CLHEP::rad);
MACE_UTILITY_LITERAL_UNIT(_mrad, CLHEP::mrad);
MACE_UTILITY_LITERAL_UNIT(_sr, CLHEP::sr);
MACE_UTILITY_LITERAL_UNIT(_deg, CLHEP::deg);

} // namespace Angle

// Time [T] symbols
inline namespace Time {

MACE_UTILITY_LITERAL_UNIT(_ns, CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_s, CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_ms, CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_us, CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_ps, CLHEP::ps);

} // namespace Time

// Energy [E] symbols
inline namespace Energy {

MACE_UTILITY_LITERAL_UNIT(_MeV, CLHEP::MeV);
MACE_UTILITY_LITERAL_UNIT(_eV, CLHEP::eV);
MACE_UTILITY_LITERAL_UNIT(_keV, CLHEP::keV);
MACE_UTILITY_LITERAL_UNIT(_GeV, CLHEP::GeV);
MACE_UTILITY_LITERAL_UNIT(_TeV, CLHEP::TeV);
MACE_UTILITY_LITERAL_UNIT(_PeV, CLHEP::PeV);

} // namespace Energy

// Mass [E][T^2][L^-2] symbols
inline namespace Mass {

MACE_UTILITY_LITERAL_UNIT(_kg, CLHEP::kg);
MACE_UTILITY_LITERAL_UNIT(_g, CLHEP::g);
MACE_UTILITY_LITERAL_UNIT(_mg, CLHEP::mg);

} // namespace Mass

// Power [E][T^-1] symbols
inline namespace Power {

MACE_UTILITY_LITERAL_UNIT(_W, CLHEP::watt);

} // namespace Power

// Force [E][L^-1] symbols
inline namespace Force {

MACE_UTILITY_LITERAL_UNIT(_N, CLHEP::newton);

} // namespace Force

// Pressure [E][L^-3] symbols
inline namespace Pressure {

MACE_UTILITY_LITERAL_UNIT(_Pa, CLHEP::hep_pascal);
MACE_UTILITY_LITERAL_UNIT(_bar, CLHEP::bar);
MACE_UTILITY_LITERAL_UNIT(_atm, CLHEP::atmosphere);

} // namespace Pressure

// Electric current [Q][T^-1] symbols
inline namespace ElectricCurrent {

MACE_UTILITY_LITERAL_UNIT(_A, CLHEP::ampere);
MACE_UTILITY_LITERAL_UNIT(_mA, CLHEP::milliampere);
MACE_UTILITY_LITERAL_UNIT(_uA, CLHEP::microampere);
MACE_UTILITY_LITERAL_UNIT(_nA, CLHEP::nanoampere);

} // namespace ElectricCurrent

// Electric potential [E][Q^-1] symbols
inline namespace ElectricPotential {

MACE_UTILITY_LITERAL_UNIT(_kV, CLHEP::kilovolt);
MACE_UTILITY_LITERAL_UNIT(_V, CLHEP::volt);

} // namespace ElectricPotential

// Electric capacitance [Q^2][E^-1] symbols
inline namespace ElectricCapacitance {

MACE_UTILITY_LITERAL_UNIT(_F, CLHEP::farad);
MACE_UTILITY_LITERAL_UNIT(_mF, CLHEP::millifarad);
MACE_UTILITY_LITERAL_UNIT(_uF, CLHEP::microfarad);
MACE_UTILITY_LITERAL_UNIT(_nF, CLHEP::nanofarad);
MACE_UTILITY_LITERAL_UNIT(_pF, CLHEP::picofarad);

} // namespace ElectricCapacitance

// Magnetic Flux [T][E][Q^-1] symbols
inline namespace MagneticFlux {

MACE_UTILITY_LITERAL_UNIT(_Wb, CLHEP::weber);

} // namespace MagneticFlux

// Magnetic flux density [T][E][Q^-1][L^-2] symbols
inline namespace MagneticFluxDensity {

MACE_UTILITY_LITERAL_UNIT(_T, CLHEP::tesla);
MACE_UTILITY_LITERAL_UNIT(_mT, 1e-3 * CLHEP::tesla);
MACE_UTILITY_LITERAL_UNIT(_uT, 1e-6 * CLHEP::tesla);
MACE_UTILITY_LITERAL_UNIT(_Gs, CLHEP::gauss);

} // namespace MagneticFluxDensity

// Inductance [T^2][E][Q^-2] symbols
inline namespace Inductance {

MACE_UTILITY_LITERAL_UNIT(_H, CLHEP::henry);
MACE_UTILITY_LITERAL_UNIT(_mH, 1e-3 * CLHEP::henry);
MACE_UTILITY_LITERAL_UNIT(_uH, 1e-6 * CLHEP::henry);
MACE_UTILITY_LITERAL_UNIT(_nH, 1e-9 * CLHEP::henry);

} // namespace Inductance

// Temperature symbols
inline namespace Temperature {

MACE_UTILITY_LITERAL_UNIT(_K, CLHEP::kelvin);

} // namespace Temperature

// Amount of substance symbols
inline namespace AmountOfSubstance {

MACE_UTILITY_LITERAL_UNIT(_mol, CLHEP::mole);

} // namespace AmountOfSubstance

// Activity [T^-1] symbols
inline namespace Activity {

MACE_UTILITY_LITERAL_UNIT(_Bq, CLHEP::Bq);
MACE_UTILITY_LITERAL_UNIT(_kBq, CLHEP::kBq);
MACE_UTILITY_LITERAL_UNIT(_MBq, CLHEP::MBq);
MACE_UTILITY_LITERAL_UNIT(_GBq, CLHEP::GBq);
MACE_UTILITY_LITERAL_UNIT(_Ci, CLHEP::Ci);
MACE_UTILITY_LITERAL_UNIT(_mCi, CLHEP::mCi);
MACE_UTILITY_LITERAL_UNIT(_uCi, CLHEP::uCi);

} // namespace Activity

// Absorbed dose [L^2][T^-2] symbols
inline namespace AbsorbedDose {

MACE_UTILITY_LITERAL_UNIT(_Gy, CLHEP::gray);
MACE_UTILITY_LITERAL_UNIT(_kGy, CLHEP::kilogray);
MACE_UTILITY_LITERAL_UNIT(_mGy, CLHEP::milligray);
MACE_UTILITY_LITERAL_UNIT(_uGy, CLHEP::microgray);

} // namespace AbsorbedDose

// Luminous intensity [I] symbols
inline namespace LuminousIntensity {

MACE_UTILITY_LITERAL_UNIT(_cd, CLHEP::candela);

} // namespace LuminousIntensity

// Luminous flux [I] symbols
inline namespace LuminousFlux {

MACE_UTILITY_LITERAL_UNIT(_lm, CLHEP::lumen);

} // namespace LuminousFlux

// Illuminance [I][L^-2] symbols
inline namespace Illuminance {

MACE_UTILITY_LITERAL_UNIT(_lux, CLHEP::lux);

} // namespace Illuminance

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// Velocity [L][T^-1] symbols
inline namespace Velocity {

MACE_UTILITY_LITERAL_UNIT(_km_ps, CLHEP::km / CLHEP::ps);
MACE_UTILITY_LITERAL_UNIT(_m_ps, CLHEP::m / CLHEP::ps);
MACE_UTILITY_LITERAL_UNIT(_cm_ps, CLHEP::cm / CLHEP::ps);
MACE_UTILITY_LITERAL_UNIT(_mm_ps, CLHEP::mm / CLHEP::ps);
MACE_UTILITY_LITERAL_UNIT(_um_ps, CLHEP::um / CLHEP::ps);
MACE_UTILITY_LITERAL_UNIT(_nm_ps, CLHEP::nm / CLHEP::ps);

MACE_UTILITY_LITERAL_UNIT(_km_ns, CLHEP::km / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_m_ns, CLHEP::m / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_cm_ns, CLHEP::cm / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_mm_ns, CLHEP::mm / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_um_ns, CLHEP::um / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_nm_ns, CLHEP::nm / CLHEP::ns);

MACE_UTILITY_LITERAL_UNIT(_km_us, CLHEP::km / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_m_us, CLHEP::m / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_cm_us, CLHEP::cm / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_mm_us, CLHEP::mm / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_um_us, CLHEP::um / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_nm_us, CLHEP::nm / CLHEP::us);

MACE_UTILITY_LITERAL_UNIT(_km_ms, CLHEP::km / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_m_ms, CLHEP::m / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_cm_ms, CLHEP::cm / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_mm_ms, CLHEP::mm / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_um_ms, CLHEP::um / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_nm_ms, CLHEP::nm / CLHEP::ms);

MACE_UTILITY_LITERAL_UNIT(_km_s, CLHEP::km / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_m_s, CLHEP::m / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_cm_s, CLHEP::cm / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_mm_s, CLHEP::mm / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_um_s, CLHEP::um / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_nm_s, CLHEP::nm / CLHEP::s);

} // namespace Velocity

// Density [E][T^2][L^-5] symbols
inline namespace Density {

MACE_UTILITY_LITERAL_UNIT(_kg_m3, CLHEP::kg / CLHEP::m3);
MACE_UTILITY_LITERAL_UNIT(_g_m3, CLHEP::g / CLHEP::m3);
MACE_UTILITY_LITERAL_UNIT(_g_cm3, CLHEP::g / CLHEP::cm3);
MACE_UTILITY_LITERAL_UNIT(_mg_cm3, CLHEP::mg / CLHEP::cm3);
MACE_UTILITY_LITERAL_UNIT(_mg_mm3, CLHEP::mg / CLHEP::mm3);

} // namespace Density

// Surface density [E][T^2][L^-4] symbols
inline namespace SurfaceDensity {

MACE_UTILITY_LITERAL_UNIT(_kg_m2, CLHEP::kg / CLHEP::m2);
MACE_UTILITY_LITERAL_UNIT(_g_m2, CLHEP::g / CLHEP::m2);
MACE_UTILITY_LITERAL_UNIT(_g_cm2, CLHEP::g / CLHEP::cm2);
MACE_UTILITY_LITERAL_UNIT(_mg_cm2, CLHEP::mg / CLHEP::cm2);
MACE_UTILITY_LITERAL_UNIT(_mg_mm2, CLHEP::mg / CLHEP::mm2);

} // namespace SurfaceDensity

// Frequency [T^-1] symbols
inline namespace Frequency {

MACE_UTILITY_LITERAL_UNIT(_Hz, 1 / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_kHz, 1 / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_MHz, 1 / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_GHz, 1 / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_THz, 1 / CLHEP::ps);

MACE_UTILITY_LITERAL_UNIT(_s_1, 1 / CLHEP::s);
MACE_UTILITY_LITERAL_UNIT(_ms_1, 1 / CLHEP::ms);
MACE_UTILITY_LITERAL_UNIT(_us_1, 1 / CLHEP::us);
MACE_UTILITY_LITERAL_UNIT(_ns_1, 1 / CLHEP::ns);
MACE_UTILITY_LITERAL_UNIT(_ps_1, 1 / CLHEP::ps);

} // namespace Frequency

// Electric field strength [E][L^-1][Q^-1] symbols
inline namespace ElectricFieldStrength {

MACE_UTILITY_LITERAL_UNIT(_V_m, CLHEP::volt / CLHEP::m);
MACE_UTILITY_LITERAL_UNIT(_V_cm, CLHEP::volt / CLHEP::cm);
MACE_UTILITY_LITERAL_UNIT(_kV_m, CLHEP::kilovolt / CLHEP::m);
MACE_UTILITY_LITERAL_UNIT(_kV_cm, CLHEP::kilovolt / CLHEP::cm);

} // namespace ElectricFieldStrength

} // namespace MACE::Utility::LiteralUnit

#undef MACE_UTILITY_LITERAL_UNIT
