#!/bin/bash
TARGET_LOG=first_fit.log
echo "Problem ID, Running Time, Total Permutations Ran, Best Buckets"
for problem in $(cat "${TARGET_LOG}"  | grep "Problem id" | awk '{ print $3 }'); do
    running_time=$(cat ${TARGET_LOG} | grep "Problem id: ${problem}" -A 11 | grep "Total running time" | awk '{ print $4 }')
    premutation_total=$(cat ${TARGET_LOG} | grep "Problem id: ${problem}" -A 11 | grep "Permutatins total:" | awk '{ print $3 }')
    best_buckets=$(cat ${TARGET_LOG} | grep "Problem id: ${problem}" -A 11 | grep "Best number of buckets:" | awk '{ print $5 }')
    echo "${problem}, ${running_time}, ${premutation_total}, ${best_buckets}"
done



