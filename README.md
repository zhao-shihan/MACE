# MACE

## How to Build

External dependencies:

    MPI-3   (MPICH, OpenMPI, Intel MPI, etc. On your frequency.)

    Geant4  (min: 4.10.7.p02)

    ROOT    (min: 6.24.02)


Builtin dependencies:

    G4mpi

    GenFit2


MACE software follows a classical cmake & make procedure, as
```shell
cd ${MACE_DIR}
mkdir build
cmake ..
make
```

## How to Run

### SimG4
In sequential mode with graphics:
```shell
./SimG4
```
In sequential mode with a macro:
```shell
./SimG4 run.mac
```
In parallel mode with a macro:
```shell
mpirun -n N ./SimG4 run.mac
```

### SimMTransport
```shell
mpirun -n N ./SimMTransport sample.cfg
```