# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mlantin/Documents/Research/VR/mocap-server/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mlantin/Documents/Research/VR/mocap-server/Unix

# Include any dependencies generated for this target.
include mocap-test/CMakeFiles/mocap-test.dir/depend.make

# Include the progress variables for this target.
include mocap-test/CMakeFiles/mocap-test.dir/progress.make

# Include the compile flags for this target's objects.
include mocap-test/CMakeFiles/mocap-test.dir/flags.make

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o: mocap-test/CMakeFiles/mocap-test.dir/flags.make
mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o: /Users/mlantin/Documents/Research/VR/mocap-server/src/mocap-test/mocap-test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mlantin/Documents/Research/VR/mocap-server/Unix/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o"
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mocap-test.dir/mocap-test.cpp.o -c /Users/mlantin/Documents/Research/VR/mocap-server/src/mocap-test/mocap-test.cpp

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mocap-test.dir/mocap-test.cpp.i"
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mlantin/Documents/Research/VR/mocap-server/src/mocap-test/mocap-test.cpp > CMakeFiles/mocap-test.dir/mocap-test.cpp.i

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mocap-test.dir/mocap-test.cpp.s"
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mlantin/Documents/Research/VR/mocap-server/src/mocap-test/mocap-test.cpp -o CMakeFiles/mocap-test.dir/mocap-test.cpp.s

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.requires:

.PHONY : mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.requires

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.provides: mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.requires
	$(MAKE) -f mocap-test/CMakeFiles/mocap-test.dir/build.make mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.provides.build
.PHONY : mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.provides

mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.provides.build: mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o


# Object files for target mocap-test
mocap__test_OBJECTS = \
"CMakeFiles/mocap-test.dir/mocap-test.cpp.o"

# External object files for target mocap-test
mocap__test_EXTERNAL_OBJECTS =

/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o
/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: mocap-test/CMakeFiles/mocap-test.dir/build.make
/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: /Users/mlantin/Documents/Research/VR/mocap-server/bin/libeasywsclient.a
/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: /usr/local/lib/libprotobuf.a
/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: /Users/mlantin/Documents/Research/VR/mocap-server/bin/libVRCom.a
/Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test: mocap-test/CMakeFiles/mocap-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mlantin/Documents/Research/VR/mocap-server/Unix/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test"
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mocap-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mocap-test/CMakeFiles/mocap-test.dir/build: /Users/mlantin/Documents/Research/VR/mocap-server/bin/mocap-test

.PHONY : mocap-test/CMakeFiles/mocap-test.dir/build

mocap-test/CMakeFiles/mocap-test.dir/requires: mocap-test/CMakeFiles/mocap-test.dir/mocap-test.cpp.o.requires

.PHONY : mocap-test/CMakeFiles/mocap-test.dir/requires

mocap-test/CMakeFiles/mocap-test.dir/clean:
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test && $(CMAKE_COMMAND) -P CMakeFiles/mocap-test.dir/cmake_clean.cmake
.PHONY : mocap-test/CMakeFiles/mocap-test.dir/clean

mocap-test/CMakeFiles/mocap-test.dir/depend:
	cd /Users/mlantin/Documents/Research/VR/mocap-server/Unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mlantin/Documents/Research/VR/mocap-server/src /Users/mlantin/Documents/Research/VR/mocap-server/src/mocap-test /Users/mlantin/Documents/Research/VR/mocap-server/Unix /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test /Users/mlantin/Documents/Research/VR/mocap-server/Unix/mocap-test/CMakeFiles/mocap-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mocap-test/CMakeFiles/mocap-test.dir/depend
