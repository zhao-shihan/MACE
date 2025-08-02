# build
# mkdir build && cd build && cmake .. && make

mkdir "Sampling_$(date "+%Y%m%d-%H:%M")" && cd "$_"

source data/mace_offline_data.sh 

read -p "Input size for sampling:" nRun

if ! [[ "$nRun" =~ ^[1-9][0-9]*$ ]]; then
    echo "Err: Not valid interger!"
    exit 1
fi

for (( i=1; i<=nRun; i++))
do 
    ../MACE GenMuonICDecay -d 1 -s 2 -o "test_mu2eeevv_run$i.root" 1000
done

echo "Sampling end."
