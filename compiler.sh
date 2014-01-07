#!/bin/bash
sh clean.sh
export TAU_MAKEFILE=/home/luoyulong/tools/tau2.23/x86_64/lib/Makefile.tau-papi-pdt

#export TAU_TRACE=1
export TAU_THROTTLE=0

export TAU_METRICS=
export COUNTER1=P_WALL_CLOCK_TIME
export COUNTER2=PAPI_FP_INS
export COUNTER4=PAPI_L1_TCM
export COUNTER5=PAPI_L2_TCM
 
 



tau_cxx.sh -c -tau_options=-optTauSelectFile=ins_file   benchmarkSets.cpp  -o benchmarkSets.o
tau_cxx.sh  benchmarkSets.o main.cpp  -o mytest 
#tau_cxx.sh -tau_options=-optTauSelectFile=ins_file  main.cpp  hps_em_comp.o -o mytest 
./mytest
sh uploadTrial.sh 
