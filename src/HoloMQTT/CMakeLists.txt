add_library (HoloMQTT HoloMQTT.cpp)

# Make sure the compiler can find include files for our HoloMQTT library
# when other libraries or executables link to HoloMQTT
target_include_directories (HoloMQTT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${MOSQUITTO_INCLUDE_DIR})
