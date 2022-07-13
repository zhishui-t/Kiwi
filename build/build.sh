#!/bin/bash
build_root=$PWD

cmake ${build_root}/../cmake
make -j8