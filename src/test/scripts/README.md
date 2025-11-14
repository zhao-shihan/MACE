# MACESW Regression Test Scripts

This directory contains scripts for running regression tests and generating regression data for MACESW.

## Scripts

### `regression_test.bash`
Runs the MACESW regression test suite, executing simulations and comparing results against reference data.

### `generate_regression_data.bash`
Generates new regression reference data from simulations.

## Usage

### Default (Physical CPU Cores)

By default, both scripts use physical CPU cores for MPI execution. This is recommended for local development and testing as it provides more stable performance:

```bash
bash build/test/regression_test.bash
bash build/test/generate_regression_data.bash
```

### Using Hardware Threads (for CI)

To utilize all hardware threads (including hyperthreading), use the `--use-hwthreads` flag. This is useful in CI environments where maximum parallelism is desired:

```bash
bash build/test/regression_test.bash --use-hwthreads
bash build/test/generate_regression_data.bash --use-hwthreads
```

## CPU Core Selection

The scripts automatically detect the number of CPU cores or hardware threads:

- **Physical Cores** (default): `nproc / threads_per_core`
  - Example: 4 hardware threads with 2 threads/core = 2 physical cores
  - More stable for local development
  - Better for systems with thermal constraints

- **Hardware Threads** (with `--use-hwthreads`): `nproc`
  - Example: 4 hardware threads (includes hyperthreading)
  - Maximum parallelism
  - Recommended for CI environments

## CI Integration

GitHub Actions workflows automatically pass the `--use-hwthreads` flag to utilize all available hardware threads in the CI environment:

```yaml
- name: Run regression test
  run: |
    . /environment
    bash build/test/regression_test.bash --use-hwthreads
```

## Platform Compatibility

The scripts work across different MPI implementations:
- **Open MPI**: Uses `--use-hwthread-cpus` or `-n` flag as appropriate
- **MPICH** and others: Uses `-n` flag with calculated core count

## Requirements

- `nproc` command (standard on Linux systems)
- `lscpu` command (standard on Linux systems)
- `bc` calculator for arithmetic operations
- MPI implementation (Open MPI, MPICH, etc.)
