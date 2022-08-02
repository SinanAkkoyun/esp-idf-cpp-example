# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
# only set if u dont use main but other dir hierarchy structure:
set(EXTRA_COMPONENT_DIRS main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(cpp_example)