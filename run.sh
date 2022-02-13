#!/usr/bin/bash 
cd "${0%/*}"
mkdir -p build
cd build
cmake ..
cmake --build . 
mv teste ..
cd ..
./teste
