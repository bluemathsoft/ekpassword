
cmake_minimum_required(VERSION 3.0.0)

project(ekstore)

if(APPLE)
  set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
  set(OPENSSL_INC_DIR "${OPENSSL_ROOT_DIR}/include")
  set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib")
endif()

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_CXX_FLAGS "-std=c++11 -O0")
set(CMAKE_EXE_LINKER_FLAGS "-L${OPENSSL_LIB_DIR}")


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/ext
  ${OPENSSL_INC_DIR}
)

file(GLOB INC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/*.h
)
file(GLOB SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

target_link_libraries(${PROJECT_NAME} crypto stdc++)
