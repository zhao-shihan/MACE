#!/bin/bash
n_physical_core=`echo "$(nproc --all) / $(lscpu | grep "Thread(s) per core" | awk '{print $4}')" | bc`

script_dir="$(dirname "$(readlink -f "$0")")"
build_dir=$script_dir/..
sample_dir=$script_dir/Sample$(date "+%Y%m%d-%H:%M")

mkdir "$sample_dir" && cd "$sample_dir"
echo "Working directory: $(pwd)"

start_time=$(date +%s)

source $build_dir/data/mace_offline_data.sh

final_exit_code=0

run_command() {
    local description="$1"
    shift
    local command=("$@")
    
    echo "Executing: $description"
    if "${command[@]}"; then
        echo "✓ $description completed"
    else
        local exit_code=$?
        echo "✗ $description failed with exit code $exit_code"
        final_exit_code=1
    fi
    echo "----------------------------------------------"
}


echo "Start simulation..."
run_command "SimMMS" mpiexec -n $n_physical_core $build_dir/MACE SimMMS $build_dir/SimMMS/run_em_flat.mac
run_command "SimVeto" mpiexec -n $n_physical_core $build_dir/MACE SimVeto $build_dir/SimVeto/run_hit_partial.mac
run_command "SimTTC" mpiexec -n $n_physical_core $build_dir/MACE SimTTC $build_dir/SimTTC/run_em_flat.mac
run_command "SimMACE" mpiexec -n $n_physical_core $build_dir/MACE SimMACE $build_dir/SimMACE/run_signal.mac

echo "Merge results..."
run_command "Merge SimMMS" hadd -ff SimMMS_em_flat_sample.root SimMMS_em_flat_test/*
run_command "Merge SimTTC" hadd -ff SimTTC_em_flat_sample.root SimTTC_em_flat_test/*
run_command "Merge SimVeto" hadd -ff SimVeto_hit_partial_sample.root SimVeto_hit_partial_test/*
run_command "Merge SimMACE" hadd -ff SimMACE_signal_sample.root SimMACE_signal_test/*

echo "Draw & save sample hists..."
run_command "GetCDCSimHit for SimMMS" root -l -q "$script_dir/GetCDCSimHit.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetMMSSimTrack for SimMMS" root -l -q "$script_dir/GetMMSSimTrack.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetVetoSimHit for SimVeto" root -l -q "$script_dir/GetVetoSimHit.cxx(\"SimVeto_hit_partial\",\"SimVeto_hit_partial_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetTTCSimHit for SimTTC" root -l -q "$script_dir/GetTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetMCPSimHit for SimMACE" root -l -q "$script_dir/GetMCPSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetTTCSimHit for SimMACE" root -l -q "$script_dir/GetTTCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetCDCSimHit for SimMACE" root -l -q "$script_dir/GetCDCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_sample.root\",\"$script_dir/mace_regression_data.root\")"
run_command "GetMMSSimTrack for SimMACE" root -l -q "$script_dir/GetMMSSimTrack.cxx(\"SimMACE_signal\",\"SimMACE_signal_sample.root\",\"$script_dir/mace_regression_data.root\")"

end_time=$(date +%s)
total_time=$((end_time - start_time))

hours=$((total_time / 3600))
minutes=$(( (total_time % 3600) / 60 ))
seconds=$((total_time % 60))

echo "=============================================="
echo "Start at: $(date -d @$start_time "+%Y-%m-%d %H:%M:%S")"
echo "End at: $(date -d @$end_time "+%Y-%m-%d %H:%M:%S")"
echo "Total running time: ${hours}h ${minutes}m ${seconds}s"
if [ $final_exit_code -eq 0 ]; then
    echo "✅ All commands completed successfully!"
else
    echo "❌ Some commands failed!"
fi
echo "Details in $sample_dir"
echo "=============================================="

exit $final_exit_code