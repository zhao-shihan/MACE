#pragma once

// #include "G4UnitSystem.hh"

namespace MACE {
    inline namespace Utility {
        namespace Unit {
            // Choose a unit system, ...

            constexpr auto K = 1.0L;

            // G4:

            constexpr auto millimeter = 1.0L;
            constexpr auto nanosecond = 1.0L;
            constexpr auto megaElectronVolt = 1.0L;
            constexpr auto m = 1e3 * millimeter;
            constexpr auto s = 1e9 * nanosecond;
            constexpr auto g = 1e-9 * megaElectronVolt * s * s / (m * m * 1.602176634e-19);

            // ROOT (Do not use for now. No way of making unit consistent so far.):

            /* constexpr auto centimeter = 1.0L;
            constexpr auto second = 1.0L;
            constexpr auto gigaElectronVolt = 1.0L;
            constexpr auto m = 1e2 * centimeter;
            constexpr auto s = second;
            constexpr auto g = 1e-12 * gigaElectronVolt * s * s / (m * m * 1.602176634e-19); */

            // ... and write down other units.

            constexpr auto nm = 1e-9 * m;
            constexpr auto um = 1e-6 * m;
            constexpr auto mm = 1e-3 * m;
            constexpr auto cm = 1e-2 * m;

            constexpr auto nm2 = nm * nm;
            constexpr auto um2 = um * um;
            constexpr auto mm2 = mm * mm;
            constexpr auto cm2 = cm * cm;
            constexpr auto m2 = m * m;

            constexpr auto nm3 = nm2 * nm;
            constexpr auto um3 = um2 * um;
            constexpr auto mm3 = mm2 * mm;
            constexpr auto cm3 = cm2 * cm;
            constexpr auto m3 = m2 * m;

            constexpr auto kg = 1e+3 * g;
            constexpr auto mg = 1e-3 * g;
            constexpr auto ug = 1e-6 * g;

            constexpr auto Pa = kg / (m * s * s);
            constexpr auto atm = 101325. * Pa;
            constexpr auto bar = 1e5 * Pa;
            constexpr auto Torr = atm / 760.;
        }

        constexpr long double operator""_K(long double val) { return val * Unit::K; }
        constexpr long double operator""_nm(long double val) { return val * Unit::nm; }
        constexpr long double operator""_um(long double val) { return val * Unit::um; }
        constexpr long double operator""_mm(long double val) { return val * Unit::mm; }
        constexpr long double operator""_cm(long double val) { return val * Unit::cm; }
        constexpr long double operator""_m(long double val) { return val * Unit::m; }
        constexpr long double operator""_kg(long double val) { return val * Unit::kg; }
        constexpr long double operator""_g(long double val) { return val * Unit::g; }
        constexpr long double operator""_mg(long double val) { return val * Unit::mg; }
        constexpr long double operator""_ug(long double val) { return val * Unit::ug; }
        constexpr long double operator""_Pa(long double val) { return val * Unit::Pa; }
        constexpr long double operator""_atm(long double val) { return val * Unit::atm; }
        constexpr long double operator""_bar(long double val) { return val * Unit::bar; }
        constexpr long double operator""_Torr(long double val) { return val * Unit::Torr; }
        constexpr long double operator""_kg_m3(long double val) { return val * (Unit::kg / Unit::m3); }
        constexpr long double operator""_g_m3(long double val) { return val * (Unit::g / Unit::m3); }
        constexpr long double operator""_g_cm3(long double val) { return val * (Unit::g / Unit::cm3); }
        constexpr long double operator""_mg_cm3(long double val) { return val * (Unit::mg / Unit::cm3); }
        constexpr long double operator""_ug_cm3(long double val) { return val * (Unit::ug / Unit::cm3); }
        constexpr long double operator""_mg_mm3(long double val) { return val * (Unit::mg / Unit::mm3); }
        constexpr long double operator""_ug_mm3(long double val) { return val * (Unit::ug / Unit::mm3); }
        constexpr long double operator""_kg_m2(long double val) { return val * (Unit::kg / Unit::m2); }
        constexpr long double operator""_g_m2(long double val) { return val * (Unit::g / Unit::m2); }
        constexpr long double operator""_g_cm2(long double val) { return val * (Unit::g / Unit::cm2); }
        constexpr long double operator""_mg_cm2(long double val) { return val * (Unit::mg / Unit::cm2); }
        constexpr long double operator""_ug_cm2(long double val) { return val * (Unit::ug / Unit::cm2); }
        constexpr long double operator""_mg_mm2(long double val) { return val * (Unit::mg / Unit::mm2); }
        constexpr long double operator""_ug_mm2(long double val) { return val * (Unit::ug / Unit::mm2); }

        constexpr long double operator""_K(unsigned long long val) { return val * Unit::K; }
        constexpr long double operator""_nm(unsigned long long val) { return val * Unit::nm; }
        constexpr long double operator""_um(unsigned long long val) { return val * Unit::um; }
        constexpr long double operator""_mm(unsigned long long val) { return val * Unit::mm; }
        constexpr long double operator""_cm(unsigned long long val) { return val * Unit::cm; }
        constexpr long double operator""_m(unsigned long long val) { return val * Unit::m; }
        constexpr long double operator""_kg(unsigned long long val) { return val * Unit::kg; }
        constexpr long double operator""_g(unsigned long long val) { return val * Unit::g; }
        constexpr long double operator""_mg(unsigned long long val) { return val * Unit::mg; }
        constexpr long double operator""_ug(unsigned long long val) { return val * Unit::ug; }
        constexpr long double operator""_Pa(unsigned long long val) { return val * Unit::Pa; }
        constexpr long double operator""_atm(unsigned long long val) { return val * Unit::atm; }
        constexpr long double operator""_bar(unsigned long long val) { return val * Unit::bar; }
        constexpr long double operator""_Torr(unsigned long long val) { return val * Unit::Torr; }
        constexpr long double operator""_kg_m3(unsigned long long val) { return val * (Unit::kg / Unit::m3); }
        constexpr long double operator""_g_m3(unsigned long long val) { return val * (Unit::g / Unit::m3); }
        constexpr long double operator""_g_cm3(unsigned long long val) { return val * (Unit::g / Unit::cm3); }
        constexpr long double operator""_mg_cm3(unsigned long long val) { return val * (Unit::mg / Unit::cm3); }
        constexpr long double operator""_ug_cm3(unsigned long long val) { return val * (Unit::ug / Unit::cm3); }
        constexpr long double operator""_mg_mm3(unsigned long long val) { return val * (Unit::mg / Unit::mm3); }
        constexpr long double operator""_ug_mm3(unsigned long long val) { return val * (Unit::ug / Unit::mm3); }
        constexpr long double operator""_kg_m2(unsigned long long val) { return val * (Unit::kg / Unit::m2); }
        constexpr long double operator""_g_m2(unsigned long long val) { return val * (Unit::g / Unit::m2); }
        constexpr long double operator""_g_cm2(unsigned long long val) { return val * (Unit::g / Unit::cm2); }
        constexpr long double operator""_mg_cm2(unsigned long long val) { return val * (Unit::mg / Unit::cm2); }
        constexpr long double operator""_ug_cm2(unsigned long long val) { return val * (Unit::ug / Unit::cm2); }
        constexpr long double operator""_mg_mm2(unsigned long long val) { return val * (Unit::mg / Unit::mm2); }
        constexpr long double operator""_ug_mm2(unsigned long long val) { return val * (Unit::ug / Unit::mm2); }
    }
}
