cmake_minimum_required (VERSION 3.0)

project (raytrace)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g  -O3")


include_directories(include)
#Get Source variables
include_directories ("${PROJECT_SOURCE_DIR}/lib")
#include Eigen
set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if(NOT EIGEN3_INCLUDE_DIR)
    message(FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()

include_directories ( "${EIGEN3_INCLUDE_DIR}" )


file(GLOB_RECURSE raytrace_SOURCES "src/*.cpp" "src/*.cc")

file(GLOB_RECURSE raytrace_HEADERS "src/*.h")

list(REMOVE_ITEM raytrace_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(raytrace_lib STATIC ${raytrace_SOURCES})


#Add C++ 11
add_executable(raytrace ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(raytrace raytrace_lib)

#Copy Resources
add_custom_command(TARGET raytrace POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:raytrace>/assets)


#Tests!
file(GLOB_RECURSE raytrace_test_sources "test/*.cpp")
add_executable(raytrace_test ${raytrace_test_sources})
target_link_libraries(raytrace_test raytrace_lib)


