#!/bin/bash

start_time=$(date +%s)

for ((i=5; i<=15; i++)); do
    for ((j=15; j<=25; j++)); do
        NAME="test_${i}X0_${j}"
        echo "$NAME is running..."
        cd ~/work/mace/build/src/app/simulation/MACE/SimEMC
        rgb zstrun ./SimEMC $NAME.mac
        rgb hadd -ff $NAME.root $NAME/*.root
    done
done

end_time=$(date +%s)
execution_time=$((end_time - start_time))

echo "All simulations are done!"
echo "Total execution time: $(($execution_time / 60)) minutes"
