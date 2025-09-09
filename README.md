# c375-fa25-lab3 — Fork, Exec, and Pipes Lab

## Overview

This lab demonstrates key Unix process concepts using C:
- Process creation (`fork`)
- Program replacement (`exec`)
- Inter-process communication (`pipe`)
- Zombie and orphan processes
- Concurrency and worker pools

## Structure

```
src/           # Demo programs
challenges/    # Challenge implementations
build/         # CMake build output
lab_report/    # Screenshots and notes (PDF)
CMakeLists.txt # Build configuration
README.md      # This file
```

## Demos

- `fork_demo`: Basic fork and wait
- `exec_demo`: Fork and exec example
- `pipe_demo`: Pipe and exec
- `pipeline_demo`: Two-child pipeline (`ls | grep`)
- `zombie_demo`: Zombie process demonstration

## Challenges

- `ch1_single_fork`: Single fork lifecycle
- `ch2_multi_fork`: Multiple children in a loop
- `ch3_exec_ls`: Exec `ls -la`
- `worker`, `ch4_exec_worker`: Exec with custom environment
- `ch5_exec_examples`: Compare `execl` and `execv`
- `ch6_pipe_sum`: Parent-to-child pipe, sum numbers
- `ch7_pipeline`: Pipeline with pattern grep
- `ch8_wait_nonblock`: Non-blocking wait for children
- `ch9_zombie`: Create and observe a zombie process
- `ch10_pool`: Parallel worker pool with concurrency limit

## Build & Run

1. **Build all executables:**
    ```bash
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
    ```

2. **Run a demo or challenge:**
    ```bash
    ./fork_demo
    ./ch2_multi_fork 5
    ./ch7_pipeline "\.c$"
    ./ch10_pool 3 file1 file2 file3
    ```

## Submission Checklist

- [x] All source files in `src/` and `challenges/`
- [x] `CMakeLists.txt` builds all executables
- [x] `lab_report.pdf` with screenshots and notes
- [x] This `README.md`
- [x] Known issues (if any) documented below

## Known Issues

- None reported.

---
