#!/bin/bash

test_dir="Test_$(date "+%Y%m%d-%H:%M")"
mkdir "$test_dir" && cd "$test_dir"
echo "Working directory: $(pwd)"

start_time=$(date +%s)

source ../../data/mace_offline_data.sh 

echo "Start simulation..."
{
    echo "Running SimMMS..."
    mpirun ../../MACE SimMMS ../../SimMMS/run_em_flat.mac
    
    echo "Running SimVeto..."
    mpirun ../../MACE SimVeto ../../SimVeto/run_hit_partial.mac
    
    echo "Running SimTTC..."
    mpirun ../../MACE SimTTC ../../SimTTC/run_em_flat.mac
    
    echo "Running SimMACE..."
    mpirun ../../MACE SimMACE ../../SimMACE/run_signal.mac

    hadd -ff SimMMS_em_flat_test.root SimMMS_em_flat_test/* 
    hadd -ff SimTTC_em_flat_test.root SimTTC_em_flat_test/* 
    hadd -ff SimVeto_hit_partial_test.root SimVeto_hit_partial_test/* 
    hadd -ff SimMACE_signal_test.root SimMACE_signal_test/* 

} > output.log 2>&1

hadd -ff SimMMS_em_flat_test/* SimMMS_em_flat_test.root
hadd -ff SimTTC_em_flat_test/* SimTTC_em_flat_test.root
hadd -ff SimVeto_hit_partial_test/* SimVeto_hit_partial_test.root
hadd -ff SimMACE_signal_test/* SimMACE_signal_test.root

echo "Start data test..."
{
    root -l -q '../TestCDCSimHit.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
    root -l -q '../TestMMSSimTrack.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
    root -l -q '../TestVetoSimHit.cxx("SimVeto_hit_partial","SimVeto_hit_partial_test.root","../Sample.root")'
    root -l -q '../TestTTCSimHit.cxx("SimTTC_em_flat","SimTTC_em_flat_test.root","../Sample.root")'
    root -l -q '../TestMCPSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestTTCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestCDCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestMMSSimTrack.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
} 2>&1 | tee -a output.log

end_time=$(date +%s)
total_time=$((end_time - start_time))

hours=$((total_time / 3600))
minutes=$(( (total_time % 3600) / 60 ))
seconds=$((total_time % 60))

echo "=============================================="
echo "Test complete!"
echo "Start time: $(date -d @$start_time "+%Y-%m-%d %H:%M:%S")"
echo "End time: $(date -d @$end_time "+%Y-%m-%d %H:%M:%S")"
echo "Total running time: ${hours}h ${minutes}m ${seconds}s"
echo "Details see output.log"
echo "=============================================="

echo "Start time: $(date -d @$start_time "+%Y-%m-%d %H:%M:%S")" >> output.log
echo "End time: $(date -d @$end_time "+%Y-%m-%d %H:%M:%S")" >> output.log
echo "Total running time: ${hours}h ${minutes}m ${seconds}s" >> output.log
echo "Total running time(s): ${total_time}s" >> output.log