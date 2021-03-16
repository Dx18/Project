cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Sources for main executable
set(MAIN_SOURCES main.cpp)

# Main executable
add_executable(Project ${MAIN_SOURCES})

# Documentation target
set(DOC_COMMAND SOURCE_DIR=${CMAKE_SOURCE_DIR} doxygen ${CMAKE_SOURCE_DIR}/Doxyfile)
add_custom_target(doc COMMAND ${DOC_COMMAND})