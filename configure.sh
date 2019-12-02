#!/bin/bash

cd isl
autoreconf -i
./configure
make -j 8
cd ..


