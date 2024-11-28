#!/bin/bash

# Setup output files
output_file="benchmark_results.csv"
validation_file="validation_results.txt"
echo "Vector Size,Version,Execution Time" > $output_file
echo "Validation Results" > $validation_file
echo "==================" >> $validation_file

# Compile programs with optimization
gcc -O3 -o sequential sequential.c
gcc -O3 -o sequential_no_vec sequential_no_vec.c
gcc -O3 -o parallel parallel.c -fopenmp -pthread

echo "Starting benchmarks..."
echo "======================="

# Test configurations
sizes=(100 1000 10000 100000 1000000)

for size in "${sizes[@]}"
do
    echo "Testing with vector size: $size"
    echo "---------------------------------------"
    
    echo -e "\nVector size: $size" >> $validation_file
    echo "-------------------" >> $validation_file
    
    # Sequential version
    echo "Sequential version:"
    output=$(./sequential $size)
    runtime=$(echo "$output" | grep -oP '(?<=Time: )[0-9.]+')
    echo "$size,Sequential,$runtime" >> $output_file
    echo "Runtime: $runtime seconds"
    echo "Sequential version:" >> $validation_file
    echo "$output" | grep -A4 "Vector validation:" >> $validation_file
    echo ""
    
    # Parallel version
    echo "Parallel version:"
    output=$(./parallel $size)
    runtime=$(echo "$output" | grep -oP '(?<=Time: )[0-9.]+')
    echo "$size,Parallel,$runtime" >> $output_file
    echo "Runtime: $runtime seconds"
    echo "Parallel version:" >> $validation_file
    echo "$output" | grep -A4 "Vector validation:" >> $validation_file
    echo ""

    # Sequential version
    echo "Sequential version without A and B vectors:"
    output=$(./sequential_no_vec $size)
    runtime=$(echo "$output" | grep -oP '(?<=Time: )[0-9.]+')
    echo "$size,Sequential-no-vec,$runtime" >> $output_file
    echo "Runtime: $runtime seconds"
    echo "Sequential-no-vec version:" >> $validation_file
    echo "$output" | grep -A4 "Vector validation:" >> $validation_file
    echo ""
    
    # Optional: clear caches between runs
    if [ -w /proc/sys/vm/drop_caches ]; then
        sync
        echo 3 > /proc/sys/vm/drop_caches
        sleep 1
    fi
    
    echo "---------------------------------------"
done

echo "Benchmark completed!"
echo "Results saved to $output_file"
echo "Results validation saved to $validation_file"

# Display the first few lines of results
echo ""
echo "Preview of benchmark results:"
head -n 5 $output_file
