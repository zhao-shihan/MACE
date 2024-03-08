# MACE

<img align="right" src="document/picture/MACE_logo_100x100.png"/>

- [MACE](#mace)
- [Dependencies](#dependencies)
  - [Toolchain](#toolchain)
  - [Libraries](#libraries)
- [Cite](#cite)
  - [The offline software system](#the-offline-software-system)
  - [The experiment](#the-experiment)

![SimMACE](document/picture/SimMACE-20220930.png)

# Dependencies

## Toolchain

1. A C++ compiler (that supports ≥ C++20. [GCC](https://gcc.gnu.org/) ≥ 12, [LLVM Clang](https://clang.llvm.org/) ≥ 15, or MSVC ≥ 19.30 (i.e., [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0))
2. A C++ library (that supports ≥ C++20. [libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/) ≥ 12, or [MSVC STL](https://github.com/microsoft/STL) with [Visual Studio](https://visualstudio.microsoft.com/) 2022 ≥ 17.0)
3. [CMake](https://cmake.org/) (≥ 3.16)
4. A build system compatible with CMake ([GNU Make](https://www.gnu.org/software/make/), [Ninja](https://ninja-build.org), or etc.)

## Libraries

Required:

1. [MPI](https://www.mpi-forum.org/) (≥ 3.0, [MPICH](https://www.mpich.org/), [OpenMPI](https://www.open-mpi.org/), [Intel MPI](https://www.intel.cn/content/www/cn/zh/developer/tools/oneapi/mpi-library.html), [Microsoft MPI](https://github.com/Microsoft/Microsoft-MPI), etc. On your frequency)
2. [Eigen](https://eigen.tuxfamily.org/) (≥ 3.4.0)
3. [Geant4](https://geant4.web.cern.ch/) (≥ 11.0.0, with GDML support)
4. [ROOT](https://root.cern/) (≥ 6.28.04)

Required, built-in if not found (network or pre-downloaded source is required):

1. [argparse](https://github.com/p-ranav/argparse) (≥ 2.6, built-in if not found)
2. [backward-cpp](https://github.com/bombela/backward-cpp) (≥ 1.6, built-in if not found)
3. [Microsoft.GSL](https://github.com/Microsoft/GSL) ([ISO C++ guidelines support library](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#gsl-guidelines-support-library)) (≥ 4.0.0, built-in if not found)
4. [PMP](https://www.pmp-library.org/) (Polygon Mesh Processing Library) (≥ 3.0.0, built-in if not found)
5. [yaml-cpp](https://github.com/jbeder/yaml-cpp) (≥ 0.8.0, built-in if not found)

# Cite

## The offline software system

1. *En attendant Godot*...

## The experiment

1. [Snowmass2021 Whitepaper: Muonium to antimuonium conversion. In 2022 Snowmass Summer Study, 3 2022.](https://arxiv.org/pdf/2203.11406)
