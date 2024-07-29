#!/bin/sh
# tst.sh

./bld.sh; if [ $? -ne 0 ]; then exit 1; fi

./persistent_state attach

./persistent_state attach

ls -l /dev/shm/

./persistent_state unlink

ls -l /dev/shm/
