#pragma once

#include "CLHEP/Units/SystemOfUnits.h"

#define MACE_UTILITY_LITERAL_UNIT_SYSTEM(suffix, unit) \
    constexpr long double operator""##suffix(long double val) { return val * (unit); } \
    constexpr long double operator""##suffix(unsigned long long val) { return val * (unit); }

namespace MACE/* ::inline Utility */ {

    // Length [L] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_nm, CLHEP::nm);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_um, CLHEP::um);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mm, CLHEP::mm);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mm2, CLHEP::mm2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mm3, CLHEP::mm3);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_cm, CLHEP::cm);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_cm2, CLHEP::cm2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_cm3, CLHEP::cm3);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_L, CLHEP::L);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_dL, CLHEP::dL);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_cL, CLHEP::cL);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mL, CLHEP::mL);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_m, CLHEP::m);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_m2, CLHEP::m2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_m3, CLHEP::m3);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_km, CLHEP::km);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_km2, CLHEP::km2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_km3, CLHEP::km3);

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_pc, CLHEP::pc);

    // Angle symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_rad, CLHEP::rad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mrad, CLHEP::mrad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_sr, CLHEP::sr);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_deg, CLHEP::deg);

    // Time [T] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ns, CLHEP::ns);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_s, CLHEP::s);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ms, CLHEP::ms);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_us, CLHEP::us);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ps, CLHEP::ps);

    // Energy [E] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_MeV, CLHEP::MeV);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_eV, CLHEP::eV);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_keV, CLHEP::keV);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_GeV, CLHEP::GeV);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_TeV, CLHEP::TeV);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_PeV, CLHEP::PeV);

    // Mass [E][T^2][L^-2] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kg, CLHEP::kg);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_g, CLHEP::g);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mg, CLHEP::mg);

    // Power [E][T^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_W, CLHEP::watt);

    // Force [E][L^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_N, CLHEP::newton);

    // Pressure [E][L^-3] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Pa, CLHEP::hep_pascal);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_bar, CLHEP::bar);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_atm, CLHEP::atmosphere);

    // Electric current [Q][T^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_A, CLHEP::ampere);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mA, CLHEP::milliampere);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uA, CLHEP::microampere);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_nA, CLHEP::nanoampere);

    // Electric potential [E][Q^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kV, CLHEP::kilovolt);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_V, CLHEP::volt);

    // Electric capacitance [Q^2][E^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_F, CLHEP::farad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mF, CLHEP::millifarad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uF, CLHEP::microfarad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_nF, CLHEP::nanofarad);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_pF, CLHEP::picofarad);

    // Magnetic Flux [T][E][Q^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Wb, CLHEP::weber);

    // Magnetic Field [T][E][Q^-1][L^-2] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_T, CLHEP::tesla);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mT, 1e-3 * CLHEP::tesla);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uT, 1e-6 * CLHEP::tesla);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Gs, CLHEP::gauss);

    // Inductance [T^2][E][Q^-2] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_H, CLHEP::henry);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mH, 1e-3 * CLHEP::henry);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uH, 1e-6 * CLHEP::henry);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_nH, 1e-9 * CLHEP::henry);

    // Temperature symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_K, CLHEP::kelvin);

    // Amount of substance symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mol, CLHEP::mole);

    // Activity [T^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Bq, CLHEP::Bq);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kBq, CLHEP::kBq);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_MBq, CLHEP::MBq);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_GBq, CLHEP::GBq);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Ci, CLHEP::Ci);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mCi, CLHEP::mCi);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uCi, CLHEP::uCi);

    // Absorbed dose [L^2][T^-2] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Gy, CLHEP::gray);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kGy, CLHEP::kilogray);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mGy, CLHEP::milligray);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_uGy, CLHEP::microgray);

    // Luminous intensity [I] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_cd, CLHEP::candela);

    // Luminous flux [I] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_lm, CLHEP::lumen);

    // Illuminance [I][L^-2] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_lux, CLHEP::lux);

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////

    // Density [E][T^2][L^-5] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kg_m3, CLHEP::kg / CLHEP::m3);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_g_m3, CLHEP::g / CLHEP::m3);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_g_cm3, CLHEP::g / CLHEP::cm3);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mg_cm3, CLHEP::mg / CLHEP::cm3);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mg_mm3, CLHEP::mg / CLHEP::mm3);

    // Surface density [E][T^2][L^-4] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kg_m2, CLHEP::kg / CLHEP::m2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_g_m2, CLHEP::g / CLHEP::m2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_g_cm2, CLHEP::g / CLHEP::cm2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mg_cm2, CLHEP::mg / CLHEP::cm2);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_mg_mm2, CLHEP::mg / CLHEP::mm2);

    // Frequency [T^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_Hz, 1 / CLHEP::s);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kHz, 1 / CLHEP::ms);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_MHz, 1 / CLHEP::us);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_GHz, 1 / CLHEP::ns);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_THz, 1 / CLHEP::ps);

    // Per unit time [T^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ns_1, 1 / CLHEP::ns);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_s_1, 1 / CLHEP::s);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ms_1, 1 / CLHEP::ms);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_us_1, 1 / CLHEP::us);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_ps_1, 1 / CLHEP::ps);

    // Electric field [E][L^-1][Q^-1] symbols

    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_V_m, CLHEP::volt / CLHEP::m);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_V_cm, CLHEP::volt / CLHEP::cm);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kV_m, CLHEP::kilovolt / CLHEP::m);
    MACE_UTILITY_LITERAL_UNIT_SYSTEM(_kV_cm, CLHEP::kilovolt / CLHEP::cm);

}

#undef MACE_UTILITY_LITERAL_UNIT_SYSTEM
