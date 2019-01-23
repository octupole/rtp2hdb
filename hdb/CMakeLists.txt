# Policy
cmake_minimum_required( VERSION 3.0) 


if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(SOURCE MyToken.cpp Residue.cpp)

add_library(hdb STATIC ${SOURCE})
