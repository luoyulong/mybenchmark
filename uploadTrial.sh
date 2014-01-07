#!/bin/bash
PERFBASE=mytest
APPNAME="27P-3D"
EXPNAME="timeExp"
TRIALNAME="test1"

taudb_loadtrial -c $PERFBASE -a $APPNAME -x $EXPNAME  -n $TRIALNAME  
