#pragma once

#include "CLHEP/Units/SystemOfUnits.h"

#include <numbers>

namespace MACE::inline Utility::LiteralUnit {

#define MACE_UTILITY_LITERAL_UNIT_DEFINITION_IMPL(FloatType, fullSuffix, unit) \
    constexpr FloatType operator""_##fullSuffix(long double value) {           \
        return value * static_cast<long double>(unit);                         \
    }                                                                          \
    constexpr FloatType operator""_##fullSuffix(unsigned long long value) {    \
        return value * static_cast<long double>(unit);                         \
    }
#define MACE_UTILITY_LITERAL_UNIT_DEFINITION(suffix, unit)             \
    MACE_UTILITY_LITERAL_UNIT_DEFINITION_IMPL(float, suffix##_f, unit) \
    MACE_UTILITY_LITERAL_UNIT_DEFINITION_IMPL(double, suffix, unit)    \
    MACE_UTILITY_LITERAL_UNIT_DEFINITION_IMPL(long double, suffix##_l, unit)

// Length [L] symbols
inline namespace Length {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm, CLHEP::nm)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um, CLHEP::um)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm, CLHEP::mm)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm, CLHEP::cm)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m, CLHEP::m)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(km, CLHEP::km)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(pc, CLHEP::pc)

} // namespace Length

// Area [L^2] symbols
inline namespace Area {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm2, CLHEP::mm2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm2, CLHEP::cm2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m2, CLHEP::m2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(km2, CLHEP::km2)

} // namespace Area

// Volume [L^3] symbols
inline namespace Volume {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm3, CLHEP::mm3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm3, CLHEP::cm3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m3, CLHEP::m3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(km3, CLHEP::km3)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(L, CLHEP::L)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(dL, CLHEP::dL)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cL, CLHEP::cL)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mL, CLHEP::mL)

} // namespace Volume

// Angle symbols
inline namespace Angle {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(rad, CLHEP::rad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mrad, CLHEP::mrad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(sr, CLHEP::sr)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(deg, CLHEP::deg)

} // namespace Angle

// Time [T] symbols
inline namespace Time {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(ns, CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(s, CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(ms, CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(us, CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(ps, CLHEP::ps)

} // namespace Time

// Energy [E] symbols
inline namespace Energy {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(MeV, CLHEP::MeV)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(eV, CLHEP::eV)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(keV, CLHEP::keV)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(GeV, CLHEP::GeV)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(TeV, CLHEP::TeV)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(PeV, CLHEP::PeV)

} // namespace Energy

// Mass [E][T^2][L^-2] symbols
inline namespace Mass {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kg, CLHEP::kg)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(g, CLHEP::g)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mg, CLHEP::mg)

} // namespace Mass

// Power [E][T^-1] symbols
inline namespace Power {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(W, CLHEP::watt)

} // namespace Power

// Force [E][L^-1] symbols
inline namespace Force {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(N, CLHEP::newton)

} // namespace Force

// Pressure [E][L^-3] symbols
inline namespace Pressure {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kPa, CLHEP::hep_pascal * 1'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(Pa, CLHEP::hep_pascal)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(bar, CLHEP::bar)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mbar, CLHEP::bar / 1'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(atm, CLHEP::atmosphere)

} // namespace Pressure

// Electric current [Q][T^-1] symbols
inline namespace ElectricCurrent {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kA, CLHEP::ampere * 1'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(A, CLHEP::ampere)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mA, CLHEP::milliampere)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uA, CLHEP::microampere)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nA, CLHEP::nanoampere)

} // namespace ElectricCurrent

// Electric potential [E][Q^-1] symbols
inline namespace ElectricPotential {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kV, CLHEP::kilovolt)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(V, CLHEP::volt)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mV, CLHEP::volt / 1'000)

} // namespace ElectricPotential

// Electric capacitance [Q^2][E^-1] symbols
inline namespace ElectricCapacitance {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(F, CLHEP::farad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mF, CLHEP::millifarad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uF, CLHEP::microfarad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nF, CLHEP::nanofarad)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(pF, CLHEP::picofarad)

} // namespace ElectricCapacitance

// Magnetic Flux [T][E][Q^-1] symbols
inline namespace MagneticFlux {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(Wb, CLHEP::weber)

} // namespace MagneticFlux

// Magnetic flux density [T][E][Q^-1][L^-2] symbols
inline namespace MagneticFluxDensity {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(T, CLHEP::tesla)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mT, CLHEP::tesla / 1'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uT, CLHEP::tesla / 1'000'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kGs, CLHEP::gauss * 1000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(Gs, CLHEP::gauss)

} // namespace MagneticFluxDensity

// Inductance [T^2][E][Q^-2] symbols
inline namespace Inductance {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(H, CLHEP::henry)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mH, CLHEP::henry / 1'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uH, CLHEP::henry / 1'000'000)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nH, CLHEP::henry / 1'000'000'000)

} // namespace Inductance

// Temperature symbols
inline namespace Temperature {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(K, CLHEP::kelvin)

} // namespace Temperature

// Amount of substance symbols
inline namespace AmountOfSubstance {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(mol, CLHEP::mole)

} // namespace AmountOfSubstance

// Activity [T^-1] symbols
inline namespace Activity {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(Bq, CLHEP::Bq)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kBq, CLHEP::kBq)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(MBq, CLHEP::MBq)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(GBq, CLHEP::GBq)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(Ci, CLHEP::Ci)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mCi, CLHEP::mCi)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uCi, CLHEP::uCi)

} // namespace Activity

// Absorbed dose [L^2][T^-2] symbols
inline namespace AbsorbedDose {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(Gy, CLHEP::gray)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kGy, CLHEP::kilogray)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mGy, CLHEP::milligray)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(uGy, CLHEP::microgray)

} // namespace AbsorbedDose

// Luminous intensity [I] symbols
inline namespace LuminousIntensity {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(cd, CLHEP::candela)

} // namespace LuminousIntensity

// Luminous flux [I] symbols
inline namespace LuminousFlux {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(lm, CLHEP::lumen)

} // namespace LuminousFlux

// Illuminance [I][L^-2] symbols
inline namespace Illuminance {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(lux, CLHEP::lux)

} // namespace Illuminance

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// Velocity [L][T^-1] symbols
inline namespace Velocity {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(km_ps, CLHEP::km / CLHEP::ps)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m_ps, CLHEP::m / CLHEP::ps)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm_ps, CLHEP::cm / CLHEP::ps)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm_ps, CLHEP::mm / CLHEP::ps)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um_ps, CLHEP::um / CLHEP::ps)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm_ps, CLHEP::nm / CLHEP::ps)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(km_ns, CLHEP::km / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m_ns, CLHEP::m / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm_ns, CLHEP::cm / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm_ns, CLHEP::mm / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um_ns, CLHEP::um / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm_ns, CLHEP::nm / CLHEP::ns)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(km_us, CLHEP::km / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m_us, CLHEP::m / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm_us, CLHEP::cm / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm_us, CLHEP::mm / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um_us, CLHEP::um / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm_us, CLHEP::nm / CLHEP::us)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(km_ms, CLHEP::km / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m_ms, CLHEP::m / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm_ms, CLHEP::cm / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm_ms, CLHEP::mm / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um_ms, CLHEP::um / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm_ms, CLHEP::nm / CLHEP::ms)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(km_s, CLHEP::km / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(m_s, CLHEP::m / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(cm_s, CLHEP::cm / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mm_s, CLHEP::mm / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(um_s, CLHEP::um / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(nm_s, CLHEP::nm / CLHEP::s)

} // namespace Velocity

// Density [E][T^2][L^-5] symbols
inline namespace Density {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kg_m3, CLHEP::kg / CLHEP::m3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(g_m3, CLHEP::g / CLHEP::m3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(g_cm3, CLHEP::g / CLHEP::cm3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mg_cm3, CLHEP::mg / CLHEP::cm3)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mg_mm3, CLHEP::mg / CLHEP::mm3)

} // namespace Density

// Surface density [E][T^2][L^-4] symbols
inline namespace SurfaceDensity {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(kg_m2, CLHEP::kg / CLHEP::m2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(g_m2, CLHEP::g / CLHEP::m2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(g_cm2, CLHEP::g / CLHEP::cm2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mg_cm2, CLHEP::mg / CLHEP::cm2)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(mg_mm2, CLHEP::mg / CLHEP::mm2)

} // namespace SurfaceDensity

// Frequency [T^-1] symbols
inline namespace Frequency {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(Hz, 1 / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kHz, 1 / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(MHz, 1 / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(GHz, 1 / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(THz, 1 / CLHEP::ps)

MACE_UTILITY_LITERAL_UNIT_DEFINITION(s_1, 1 / CLHEP::s)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(ms_1, 1 / CLHEP::ms)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(us_1, 1 / CLHEP::us)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(ns_1, 1 / CLHEP::ns)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(ps_1, 1 / CLHEP::ps)

} // namespace Frequency

// Electric field strength [E][L^-1][Q^-1] symbols
inline namespace ElectricFieldStrength {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(V_m, CLHEP::volt / CLHEP::m)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(V_cm, CLHEP::volt / CLHEP::cm)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kV_m, CLHEP::kilovolt / CLHEP::m)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(kV_cm, CLHEP::kilovolt / CLHEP::cm)

} // namespace ElectricFieldStrength

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

inline namespace MathConstant {

MACE_UTILITY_LITERAL_UNIT_DEFINITION(log2e, std::numbers::log2e_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(log10e, std::numbers::log10e_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(pi, std::numbers::pi_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(inv_pi, std::numbers::inv_pi_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(inv_sqrtpi, std::numbers::inv_sqrtpi_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(log2, std::numbers::ln2_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(log10, std::numbers::ln10_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(sqrt2, std::numbers::sqrt2_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(sqrt3, std::numbers::sqrt3_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(inv_sqrt3, std::numbers::inv_sqrt3_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(egamma, std::numbers::egamma_v<long double>)
MACE_UTILITY_LITERAL_UNIT_DEFINITION(phi, std::numbers::phi_v<long double>)

} // namespace MathConstant

#undef MACE_UTILITY_LITERAL_UNIT_DEFINITION
#undef MACE_UTILITY_LITERAL_UNIT_DEFINITION_IMPL

} // namespace MACE::inline Utility::LiteralUnit
