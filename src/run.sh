#!/bin/bash
#LISTOFFILES=list_of_5_items.txt
LISTOFFILES=../res/list_of_files.txt
LOGDIR=logs/
./main --from-files ${LISTOFFILES} --max-solving-time 60 --exhaustive > ${LOGDIR}one_min.log
./main --from-files ${LISTOFFILES} --max-solving-time 600 --exhaustive > ${LOGDIR}ten_min.log
./main --from-files ${LISTOFFILES} --max-solving-time 60 --firstfit >  ${LOGDIR}first_fit.log

