cmake_minimum_required(VERSION 3.4)

project(mocap-server)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (VICON_LIB "${PROJECT_SOURCE_DIR}/../lib/Vicon_DataStream_SDK_1.3.0.57137h_MAC")
include_directories(${PROJECT_SOURCE_DIR} ${VICON_LIB} ${EASYWSCLIENT_LIB})

add_library(vicon SHARED IMPORTED)
set_property(TARGET vicon PROPERTY IMPORTED_LOCATION "${VICON_LIB}/libViconDataStreamSDK_CPP.dylib")

add_subdirectory(easywsclient)

add_executable(mocap-server mocap-server.cpp)
target_link_libraries(mocap-server vicon easywsclient)