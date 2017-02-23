#!/bin/bash
for i in `seq 1 20`; do
   title=`cat raw.txt | awk "{print $"${i}"}" | grep HARD`
   cat raw.txt | awk "{print $"${i}"}" | grep -v HARD > "${title}.txt"
   sed -i '/^$/d' "${title}.txt"
done
