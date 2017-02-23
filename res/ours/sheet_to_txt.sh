#!/bin/bash -x
for i in `seq 1 100`; do
   title=`cat raw.txt | awk "{print $"${i}"}" | grep _`
   cat raw.txt | awk "{print $"${i}"}" | grep -v _ > "${title}.txt"
   sed -i '/^$/d' "${title}.txt"
done
