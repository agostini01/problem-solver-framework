#!/bin/bash

mkdir ampl
for i in $@; do
    if [[ $i == *".txt" ]]; then
	echo "Converting ${i}"
        num_items=`cat ${i}| sed -n 1p`
	size_bins=`cat ${i}| sed -n 2p`
        pushd ampl
	folder_name=`echo ${i} | sed 's/.txt//'`
	mkdir $folder_name
	pushd $folder_name
	touch "${folder_name}.mod"
	echo "set BINS:=1..${num_items};" >> ${folder_name}.mod
	echo "set ITEMS:=1..${num_items};" >> ${folder_name}.mod

        echo "param bin_size:=${size_bins};" >> ${folder_name}.mod
        echo "param size{i in ITEMS};"  >> ${folder_name}.mod
	touch ${folder_name}.dat
	echo "param size:=" >> ${folder_name}.dat

	touch ${folder_name}.run
        echo "option solver cplex;" >> ${folder_name}.run
        echo "option cplex_options \"timelimit=30\"; " >> ${folder_name}.run
        echo "option cplex_options 'timing 1';" >> ${folder_name}.run
        echo "model ${folder_name}.mod;" >> ${folder_name}.run
        echo "model binpack.mod;" >> ${folder_name}.run
        echo "data ${folder_name}.dat;" >> ${folder_name}.run
        echo "update data;" >> ${folder_name}.run
        echo "update data BINS;" >> ${folder_name}.run
        echo "update data ITEMS;" >> ${folder_name}.run
        echo "update data bin_size;" >> ${folder_name}.run
        echo "solve;" >> ${folder_name}.run
        echo "display open;" >> ${folder_name}.run
        echo "display x;" >> ${folder_name}.run
        echo "display Bins;" >> ${folder_name}.run
        echo "display size;" >> ${folder_name}.run

	popd
        popd
	let j=1
	for line in `cat $i | tail -n +3`; do
       	    pushd ampl
	    pushd $folder_name
            echo "${j} ${line}" >> ${folder_name}.dat
            popd
            popd
            let j=$j+1
	done
        pushd ampl
        pushd $folder_name
	echo ";" >> ${folder_name}.dat
        popd
        popd

        cp ampl_res/binpack.mod ampl/${folder_name}
    fi
done
