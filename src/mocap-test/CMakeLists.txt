add_executable(mocap-test mocap-test.cpp)
target_link_libraries(mocap-test easywsclient protobuf_lib VRCom)
target_compile_features(mocap-test PUBLIC cxx_range_for)