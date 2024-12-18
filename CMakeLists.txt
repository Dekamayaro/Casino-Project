cmake_minimum_required(VERSION 3.20)
project(McMoney_Pit)

set(PROJECT_VERSION "1.0.0")

# Set runtime output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")

# Set compiler version and standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(MoneyPit ${SRC_FILES})

target_link_libraries(MoneyPit)

get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)

# TO MAKE TESTS YOU MUST BE IN THE TEST DIRECTORY AND RUN `cmake .` + `make`.
# TO MAKE THE PROGRAM ITSELF YOU MUST BE IN THE ROOT DIRECTORY OF THE REPOSITORY AND RUN `cmake .` + `make`.
if (CURRENT_DIR STREQUAL ${CMAKE_SOURCE_DIR})
    message(STATUS "Running from the root directory, skipping GoogleTest setup.")
else()
    message(STATUS "Running from an unknown directory: ${CURRENT_DIR}")
endif()