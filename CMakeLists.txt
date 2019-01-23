# Policy
cmake_minimum_required( VERSION 3.0) 


# Project name
project(rtp2hdb CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(CheckCXXSymbolExists)

FIND_PACKAGE( Boost 1.51 COMPONENTS program_options regex REQUIRED )

message(STATUS "Here are the ${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIRS})

link_libraries(${Boost_LIBRARIES})

include_directories("include")
include_directories("hdb")
add_subdirectory(hdb)
add_executable(rtp2hdb rtp2hdb.cpp)

target_link_libraries(rtp2hdb hdb)

