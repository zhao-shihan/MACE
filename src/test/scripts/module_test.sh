#!/bin/bash
n_physical_core=$(echo "$(nproc --all) / $(env LC_ALL=C lscpu | grep "Thread(s) per core" | awk '{print $4}')" | bc)

script_dir="$(dirname "$(readlink -f "$0")")"
build_dir=$script_dir/..
test_dir=$script_dir/Test_$(date "+%Y%m%d-%H:%M")

mkdir "$test_dir" && cd "$test_dir"
echo "Working directory: $(pwd)"

start_time=$(date +%s)

source $build_dir/data/mace_offline_data.sh

final_exit_code=0

run_command() {
    local command=("$@")
    if "${command[@]}"; then
        echo "✓ $command completed"
    else
        local exit_code=$?
        echo "✗ $command failed with exit code $exit_code"
        final_exit_code=1
    fi
    echo "----------------------------------------------"
}

echo "Start simulation..."
run_command mpiexec -n $n_physical_core -bind-to core $build_dir/MACE SimMMS $build_dir/SimMMS/run_em_flat.mac
run_command mpiexec -n $n_physical_core -bind-to core $build_dir/MACE SimVeto $build_dir/SimVeto/run_hit_partial.mac
run_command mpiexec -n $n_physical_core -bind-to core $build_dir/MACE SimTTC $build_dir/SimTTC/run_em_flat.mac
run_command mpiexec -n $n_physical_core -bind-to core $build_dir/MACE SimMACE $build_dir/SimMACE/run_signal.mac

echo "Merging results..."
run_command hadd -ff SimMMS_em_flat_test.root SimMMS_em_flat_test/*
run_command hadd -ff SimTTC_em_flat_test.root SimTTC_em_flat_test/*
run_command hadd -ff SimVeto_hit_partial_test.root SimVeto_hit_partial_test/*
run_command hadd -ff SimMACE_signal_test.root SimMACE_signal_test/*

echo "Start data test..."
run_command root -l -q "$script_dir/TestCDCSimHit.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestMMSSimTrack.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestVetoSimHit.cxx(\"SimVeto_hit_partial\",\"SimVeto_hit_partial_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestMCPSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestTTCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestCDCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$script_dir/mace_regression_data.root\")"
run_command root -l -q "$script_dir/TestMMSSimTrack.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$script_dir/mace_regression_data.root\")"

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
echo "Details in $test_dir"
echo "=============================================="

exit $final_exit_code