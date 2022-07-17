#!/bin/bash
build_root=$PWD

cmake -DCMAKE_BUILD_TYPE=Debug ${build_root}/../cmake
make -j8