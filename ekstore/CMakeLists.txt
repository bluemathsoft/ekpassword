
cmake_minimum_required(VERSION 3.0.0)

project(ekstore)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_CXX_FLAGS "-std=c++11 -O0")
set(CMAKE_EXE_LINKER_FLAGS "")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

file(GLOB INC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
)
file(GLOB SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

target_link_libraries(${PROJECT_NAME} crypto stdc++)
