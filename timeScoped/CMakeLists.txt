cmake_minimum_required(VERSION 3.30.3)
project(tool-timeScoped)
set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(. SRC_LISTS)
add_executable(timeScoped ${SRC_LISTS})