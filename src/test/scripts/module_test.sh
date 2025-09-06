#!/bin/bash

test_dir="Test_$(date "+%Y%m%d-%H:%M")"
mkdir "$test_dir" && cd "$test_dir"
echo "Working directory: $(pwd)"

start_time=$(date +%s)

source ../../data/mace_offline_data.sh 

echo "Start simulation..."
{
    echo "Running SimMMS..."
    ../../MACE SimMMS ../../SimMMS/run_em_flat.mac
    
    echo "Running SimVeto..."
    ../../MACE SimVeto ../../SimVeto/run_hit_partial.mac
    
    echo "Running SimTTC..."
    ../../MACE SimTTC ../../SimTTC/run_em_flat.mac
    
    echo "Running SimMACE..."
    ../../MACE SimMACE ../../SimMACE/run_signal.mac
} > output.log 2>&1

echo "Start data test..."
{
    root -l -q '../TestCDCSimHit.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
    root -l -q '../TestMMSSimTrack.cxx("SimMMS_em_flat","SimMMS_em_flat_test.root","../Sample.root")'
    root -l -q '../TestVetoSimHit.cxx("SimVeto_hit_partial","SimVeto_hit_partial_test.root","../Sample.root")'
    root -l -q '../TestTTCSimHit.cxx("SimTTC_em_flat","TTC_em_flat_test.root","../Sample.root")'
    root -l -q '../TestMCPSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestTTCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestCDCSimHit.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
    root -l -q '../TestMMSSimTrack.cxx("SimMACE_signal","SimMACE_signal_test.root","../Sample.root")'
} >> output.log 2>&1

end_time=$(date +%s)
total_time=$((end_time - start_time))

hours=$((total_time / 3600))
minutes=$(( (total_time % 3600) / 60 ))
seconds=$((total_time % 60))

echo "=============================================="
echo "Test complete!"
echo "Start time: $(date -d @$start_time "+%Y-%m-%d %H:%M:%S")"
echo "End time: $(date -d @$end_time "+%Y-%m-%d %H:%M:%S")"
echo "Total running time: ${hours}小时 ${minutes}分钟 ${seconds}秒"
echo "Details: output.log"
echo "=============================================="

echo "Start time: $(date -d @$start_time "+%Y-%m-%d %H:%M:%S")" >> output.log
echo "End time: $(date -d @$end_time "+%Y-%m-%d %H:%M:%S")" >> output.log
echo "Total running time: ${hours}小时 ${minutes}分钟 ${seconds}秒" >> output.log
echo "Total running time(秒): ${total_time}秒" >> output.log