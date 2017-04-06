add_library (flatbuf holojam_generated.cc)

# Make sure the compiler can find include files for our library
# when other libraries or executables link to holojam_generated
target_include_directories (flatbuf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${GOOGLE_FLATBUF_LIB})
