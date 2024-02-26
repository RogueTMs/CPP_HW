cmake_minimum_required(VERSION 3.28)

project(CPP_HW LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(googletest)




SET(EXCECUTABLE_NAME "Task1")

add_executable(${EXCECUTABLE_NAME}.x "")

target_sources(
  ${EXCECUTABLE_NAME}.x
  PRIVATE
  ${EXCECUTABLE_NAME}.cpp
)

target_link_libraries(${EXCECUTABLE_NAME}.x gtest_main gmock_main)