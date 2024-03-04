cmake_minimum_required(VERSION 3.22)

project(CPP_HW LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



SET(EXCECUTABLE_NAME "Task1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

add_executable(${EXCECUTABLE_NAME}.x "")

target_link_libraries(${EXCECUTABLE_NAME}.x gtest gmock pthread)

target_sources(
  ${EXCECUTABLE_NAME}.x
  PRIVATE
  ${EXCECUTABLE_NAME}.cpp
)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

