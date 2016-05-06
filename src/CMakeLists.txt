cmake_minimum_required(VERSION 3.4)

project(mocap-server)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (EXT_LIB "${PROJECT_SOURCE_DIR}/../lib")
include_directories(${PROJECT_SOURCE_DIR} ${EXT_LIB})

add_library(vicon SHARED IMPORTED)
set_property(TARGET vicon PROPERTY IMPORTED_LOCATION "${EXT_LIB}/Vicon_DataStream_SDK_1.3.0.57137h_MAC/libViconDataStreamSDK_CPP.dylib")

add_library(protobuf_lib STATIC IMPORTED)
set_property(TARGET protobuf_lib PROPERTY IMPORTED_LOCATION /usr/local/lib/libprotobuf.a)

add_subdirectory(easywsclient)
add_subdirectory(protobuf)
add_subdirectory(mocap-test)

add_executable(mocap-server mocap-server.cpp)
target_link_libraries(mocap-server vicon easywsclient protobuf_lib VRCom)
target_compile_features(mocap-server PUBLIC cxx_range_for)

