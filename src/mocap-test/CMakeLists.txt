add_executable(mocap-test mocap-test.cpp)
target_link_libraries(mocap-test flatbuf smallUDPClient easywsclient flatbuf_lib protobuf_lib boost_system_mt_lib VRCom)
target_compile_features(mocap-test PUBLIC cxx_range_for)
