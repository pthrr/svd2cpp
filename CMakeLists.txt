cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectSettings.cmake)

project(
  svd2cpp
  LANGUAGES C CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "svd2cpp")

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(cxxopts REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_subdirectory(src)
