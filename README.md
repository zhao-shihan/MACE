# MACE

[![GitHub License](https://img.shields.io/github/license/zhao-shihan/MACE?color=red)](COPYING)
![GitHub Created At](https://img.shields.io/github/created-at/zhao-shihan/MACE?color=green)
![GitHub top language](https://img.shields.io/github/languages/top/zhao-shihan/MACE?color=f34b7d)
[![GitHub activity](https://img.shields.io/github/commit-activity/m/zhao-shihan/MACE)](https://github.com/zhao-shihan/MACE/pulse)
![GitHub last commit](https://img.shields.io/github/last-commit/zhao-shihan/MACE)
![GitHub repo size](https://img.shields.io/github/repo-size/zhao-shihan/MACE)

[![Regression test (AMD64 GNU/Linux GCC)](https://github.com/zhao-shihan/MACE/actions/workflows/regression-test-with-gcc.yml/badge.svg)](https://github.com/zhao-shihan/MACE/actions/workflows/regression-test-with-gcc.yml)
[![Regression test (AMD64 GNU/Linux Clang, unity build)](https://github.com/zhao-shihan/MACE/actions/workflows/regression-test-with-clang.yml/badge.svg)](https://github.com/zhao-shihan/MACE/actions/workflows/regression-test-with-clang.yml)

- [MACE](#mace)
  - [Dependencies](#dependencies)
    - [Toolchain](#toolchain)
    - [Libraries](#libraries)
  - [Cite](#cite)

![MACE](document/picture/MACE_logo_v2.svg)

<!-- ## Pre-built binaries

Pre-built, optimized binaries are available through [Apptainer](https://apptainer.org/) (formerly known as Singularity).

For more information, please check out [the image repository homepage](https://github.com/zhao-shihan/MACE-apptainer). -->

## Dependencies

### Toolchain

1. A C++ compiler (that supports ≥ C++20. [GCC](https://gcc.gnu.org/) ≥ 12, [LLVM Clang](https://clang.llvm.org/) ≥ 16, or MSVC ≥ 19.30 (i.e., [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0))
2. A C++ library (that supports ≥ C++20. [libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/) ≥ 12, or [MSVC STL](https://github.com/microsoft/STL) with [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0)
3. [CMake](https://cmake.org/) (≥ 3.21)
4. A build system compatible with CMake ([GNU Make](https://www.gnu.org/software/make/), [Ninja](https://ninja-build.org), or etc.)

### Libraries

Required:

1. [Mustard (A modern, distributed offline software framework for HEP experiments)](https://github.com/zhao-shihan/Mustard) (≥ 0.25.1015, built-in if not found)

Required, built-in if not found (network or pre-downloaded source is required):

1. [zhao-shihan/GenFit (A generic track-fitting toolkit)](https://github.com/zhao-shihan/GenFit) (a GenFit fork, built-in if not found)
2. [PMP (Polygon Mesh Processing Library)](https://www.pmp-library.org/) (≥ 3.0.0, built-in if not found)
3. [MACE offline data](https://code.ihep.ac.cn/zhaoshh7/mace_offline_data) (built-in if not found)

## Cite

1. [A.-Y. Bai et al. (MACE working group), Conceptual Design of the Muonium-to-Antimuonium Conversion Experiment (MACE), arXiv:1410.18817.](https://arxiv.org/abs/2410.18817)
2. [Siyuan Chen, Shihan Zhao, Weizhi Xiong et al., Design of a CsI(Tl) calorimeter for muonium-to-antimuonium conversion experiment, Front.Phys. 20 (2025) 035202](https://doi.org/10.15302/frontphys.2025.035202)
3. [Shihan Zhao and Jian Tang, Optimization of muonium yield in perforated silica aerogel, Phys.Rev.D 109 (2024) 7, 072012.](https://doi.org/10.1103/PhysRevD.109.072012)
4. [A.-Y. Bai et al. (MACE working group), Snowmass2021 Whitepaper: Muonium to antimuonium conversion, in 2022 Snowmass Summer Study (2022), arXiv:2203.11406.](https://arxiv.org/abs/2203.11406)
