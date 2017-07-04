add_executable(mocap-test mocap-test.cpp)
target_link_libraries(mocap-test ${MOSQUITTO_LIBRARIES} ${LDFLAGS_EX} -rdynamic)
target_link_libraries(mocap-test flatbuf HoloMQTT flatbuf_lib)
target_compile_features(mocap-test PUBLIC cxx_range_for)
