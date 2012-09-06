cmake_minimum_required (VERSION 2.6)

# Project settings
project (roubo)

# Dependencies
include_directories (${CMAKE_SOURCE_DIR}/lib/utf8cpp/source)

# Subdirectories
add_subdirectory (src)
