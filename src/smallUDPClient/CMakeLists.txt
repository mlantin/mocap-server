add_library (smallUDPClient smallUDPClient.cpp)

# Make sure the compiler can find include files for our smallUDPClient library
# when other libraries or executables link to smallUDPClient
target_include_directories (smallUDPClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${BOOST_LIB})
