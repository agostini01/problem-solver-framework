#!/bin/bash
for i in $@; do
  pushd $i
  ampl ${i}.run
  popd
done

