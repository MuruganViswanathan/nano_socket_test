#   Copyright 2010-2017 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

cmake_minimum_required(VERSION 2.8.7)

project(test_nanomsg)

include(ExternalProject)

set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/_install)
set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR}/_prefix)
set(INCLUDE_DIR ${INSTALL_DIR}/include)
set(LIBRARY_DIR ${INSTALL_DIR}/lib)
set(LIBRARY_DIR64 ${INSTALL_DIR}/lib64)
set(COMMON_LIBRARY_DIR ${INSTALL_DIR}/lib/${CMAKE_LIBRARY_ARCHITECTURE})
set(TEST_RESULTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_results)
file(MAKE_DIRECTORY ${TEST_RESULTS_DIR})

include_directories(${INCLUDE_DIR})

# Get git commit hash 
#-------------------------------------------------------------------------------
execute_process(
  COMMAND git describe --tags --always
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DGIT_COMMIT_TAG=\"${GIT_COMMIT_TAG}\"")	

# Compile options/flags
#-------------------------------------------------------------------------------
add_definitions(-std=c99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -DNOPOLL_LOGGER ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wno-missing-field-initializers")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

if (NOT BUILD_YOCTO)

# nanoMsg external dependency
#-------------------------------------------------------------------------------
ExternalProject_Add(nanomsg
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/_prefix/nanomsg
    GIT_REPOSITORY https://github.com/nanomsg/nanomsg.git
    GIT_TAG "master"
    CMAKE_ARGS += -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -DBUILD_TESTING=OFF
)
add_library(libnanomsg STATIC SHARED IMPORTED)
add_dependencies(libnanomsg nanomsg)

endif ()

link_directories ( ${LIBRARY_DIR} ${LIBRARY_DIR64} ${COMMON_LIBRARY_DIR} ${MAIN_PROJ_COMMON_PATH} ${MAIN_PROJ_LIB_PATH} ${MAIN_PROJ_LIB64_PATH} )

add_subdirectory(src)

