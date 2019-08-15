cmake_minimum_required(VERSION 2.8)
project(sentence_splitter_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/lib)

set(SOURCE_FILES sentence_splitter.cpp)

add_executable(sentsplit main.cpp ${SOURCE_FILES})
add_executable(testcase test_splitter.cpp ${SOURCE_FILES})
target_link_libraries(testcase gtest gtest_main gmock)