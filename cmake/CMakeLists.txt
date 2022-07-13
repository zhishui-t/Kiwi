cmake_minimum_required(VERSION 3.20)

project(zrpc)

set (CFLAGE "${CFLAGE} -std=c11")

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS_DEBUG "${CFLAGE} -g")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall ${CFLAGE}")

set(KIWI_ROOT_PATH ${PROJECT_SOURCE_DIR}/..)

set(KIWI_3rd_PATH ${KIWI_ROOT_PATH}/3rd)
set(KIWI_SOURCE_PATH ${KIWI_ROOT_PATH}/src)
set(EXECUTABLE_OUTPUT_PATH ${KIWI_ROOT_PATH}/bin)
set(LIBRARY_OUTPUT_PATH ${KIWI_ROOT_PATH}/lib)

add_subdirectory(src)