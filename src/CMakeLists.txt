cmake_minimum_required(VERSION 3.4)

project(mocap-server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (EXT_LIB "${PROJECT_SOURCE_DIR}/../lib")
set (GOOGLE_PROTOBUF_LIB /usr/local/opt/protobuf/include)
set (GOOGLE_FLATBUF_LIB /usr/local/Cellar/flatbuffers/1.6.0/include)
set (BOOST_LIB /opt/local/include)

include_directories(${PROJECT_SOURCE_DIR} ${EXT_LIB} ${GOOGLE_PROTOBUF_LIB})
include_directories(${PROJECT_SOURCE_DIR} ${EXT_LIB} ${GOOGLE_FLATBUF_LIB})
include_directories(${PROJECT_SOURCE_DIR} ${EXT_LIB} ${BOOST_LIB})

add_library(vicon SHARED IMPORTED)
set_property(TARGET vicon PROPERTY IMPORTED_LOCATION "${EXT_LIB}/Vicon_DataStream_SDK_1.3.0.57137h_MAC/libViconDataStreamSDK_CPP.dylib")

add_library(protobuf_lib STATIC IMPORTED)
add_library(flatbuf_lib STATIC IMPORTED)
add_library(boost_system_mt_lib STATIC IMPORTED)

set_property(TARGET protobuf_lib PROPERTY IMPORTED_LOCATION /usr/local/lib/libprotobuf.a)
set_property(TARGET flatbuf_lib PROPERTY IMPORTED_LOCATION /usr/local/lib/libflatbuffers.a)
set_property(TARGET boost_system_mt_lib PROPERTY IMPORTED_LOCATION /opt/local/lib/libboost_system-mt.a)

add_subdirectory(easywsclient)
add_subdirectory(smallUDPClient)
add_subdirectory(protobuf)
add_subdirectory(flatbuf)
add_subdirectory(mocap-test)

add_executable(mocap-server mocap-server.cpp)
target_link_libraries(mocap-server vicon flatbuf smallUDPClient easywsclient protobuf_lib flatbuf_lib boost_system_mt_lib VRCom)
target_compile_features(mocap-server PUBLIC cxx_range_for)
