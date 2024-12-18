cmake_minimum_required(VERSION 3.20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Set compiler version and standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(googletest)

message(STATUS "Running from the 'test' directory, proceeding with GoogleTest setup.")

add_executable(runAllTests
  ../src/player.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/runner.cpp
  ../src/card.cpp 
  ../src/slots.cpp
  ../src/roulette.cpp
  ../src/blackjack.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  test.cpp
  runnertest.cpp
  slotstest.cpp
  blackjacktest.cpp
  bartest.cpp
  roulettetest.cpp
)

add_executable(slotsTests
  ../src/player.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/runner.cpp
  ../src/card.cpp 
  ../src/slots.cpp
  ../src/roulette.cpp
  ../src/blackjack.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  slotstest.cpp
)

add_executable(blackjackTests
  ../src/player.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/runner.cpp
  ../src/card.cpp 
  ../src/slots.cpp
  ../src/roulette.cpp
  ../src/blackjack.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  blackjacktest.cpp
)

add_executable(runnerTests
  ../src/player.cpp
  ../src/runner.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/slots.cpp
  ../src/blackjack.cpp
  ../src/roulette.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  runnertest.cpp
)

add_executable(barTests
  ../src/player.cpp
  ../src/runner.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/slots.cpp
  ../src/blackjack.cpp
  ../src/roulette.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  bartest.cpp
)

add_executable(rouletteTests
  ../src/player.cpp
  ../src/runner.cpp
  ../src/bar.cpp
  ../src/card.cpp
  ../src/slots.cpp
  ../src/blackjack.cpp
  ../src/roulette.cpp
  ../src/menumanager.cpp
  ../src/visuals.cpp
  roulettetest.cpp
)

target_link_libraries(runAllTests gmock gtest gtest_main)
target_link_libraries(slotsTests gmock gtest gtest_main)
target_link_libraries(runnerTests gmock gtest gtest_main)
target_link_libraries(blackjackTests gmock gtest gtest_main)
target_link_libraries(barTests gmock gtest gtest_main)
target_link_libraries(rouletteTests gmock gtest gtest_main)
