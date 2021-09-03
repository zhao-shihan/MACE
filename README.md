# MACE

# How to Build

Dependencies:
    MPI-3   (MPICH, OpenMPI, etc., on your frequency.)
    Geant4  (min: 4.10.7.p02)
    G4mpi   (you can find it at ${G4_DIR}/share/Geant4(...)/examples/extended/parallel/MPI)
    ROOT    (min: 6.24.02)

MACE software follows a classical cmake & make procedure, as
```shell
cd ${MACE_DIR}
mkdir build
cmake ..
make
```

# How to Run

## SimG4
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

## SimMTransport
```shell
mpirun -n N ./SimMTransport sample.cfg
```