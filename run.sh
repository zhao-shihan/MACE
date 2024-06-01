#!/bin/bash

cd ~/work/mace/pen-int-unified/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun -n 16 ./SimMACEPhaseI test.mac
hadd -ff pen-int-unified.root typePEN/*.root
mv pen-int-unified.root ~/work/mace/surfaceTest

cd ~/work/mace/pen-int-davis-air/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun -n 16 ./SimMACEPhaseI test.mac
hadd -ff pen-int-davis-air.root typePEN/*.root
mv pen-int-davis-air.root ~/work/mace/surfaceTest

cd ~/work/mace/pen-int-davis-grease/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun -n 16 ./SimMACEPhaseI test.mac
hadd -ff pen-int-davis-grease.root typePEN/*.root
mv pen-int-davis-grease.root ~/work/mace/surfaceTest

cd ~/work/mace/pen-int-davis-teflon/src/app/simulation/MACE/PhaseI/SimMACEPhaseI
mpirun -n 16 ./SimMACEPhaseI test.mac
hadd -ff pen-int-davis-teflon.root typePEN/*.root
mv pen-int-davis-teflon.root ~/work/mace/surfaceTest

echo "All simulations are done!"