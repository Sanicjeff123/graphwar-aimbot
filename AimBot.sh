#!/bin/sh
if [ -x AcquirePoints ]
then
   ./AcquirePoints | python2.7 python/BuildEquation.py
else
   echo "Could not find AcquirePoints executable - maybe you need to run make first"
fi
