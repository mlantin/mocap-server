# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ralek/mocap-server/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ralek/mocap-server/unix

# Include any dependencies generated for this target.
include protobuf/CMakeFiles/VRCom.dir/depend.make

# Include the progress variables for this target.
include protobuf/CMakeFiles/VRCom.dir/progress.make

# Include the compile flags for this target's objects.
include protobuf/CMakeFiles/VRCom.dir/flags.make

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o: protobuf/CMakeFiles/VRCom.dir/flags.make
protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o: /Users/ralek/mocap-server/src/protobuf/VRCom.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ralek/mocap-server/unix/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o"
	cd /Users/ralek/mocap-server/unix/protobuf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VRCom.dir/VRCom.pb.cc.o -c /Users/ralek/mocap-server/src/protobuf/VRCom.pb.cc

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VRCom.dir/VRCom.pb.cc.i"
	cd /Users/ralek/mocap-server/unix/protobuf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ralek/mocap-server/src/protobuf/VRCom.pb.cc > CMakeFiles/VRCom.dir/VRCom.pb.cc.i

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VRCom.dir/VRCom.pb.cc.s"
	cd /Users/ralek/mocap-server/unix/protobuf && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ralek/mocap-server/src/protobuf/VRCom.pb.cc -o CMakeFiles/VRCom.dir/VRCom.pb.cc.s

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.requires:

.PHONY : protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.requires

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.provides: protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.requires
	$(MAKE) -f protobuf/CMakeFiles/VRCom.dir/build.make protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.provides.build
.PHONY : protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.provides

protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.provides.build: protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o


# Object files for target VRCom
VRCom_OBJECTS = \
"CMakeFiles/VRCom.dir/VRCom.pb.cc.o"

# External object files for target VRCom
VRCom_EXTERNAL_OBJECTS =

/Users/ralek/mocap-server/bin/libVRCom.a: protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o
/Users/ralek/mocap-server/bin/libVRCom.a: protobuf/CMakeFiles/VRCom.dir/build.make
/Users/ralek/mocap-server/bin/libVRCom.a: protobuf/CMakeFiles/VRCom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ralek/mocap-server/unix/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library /Users/ralek/mocap-server/bin/libVRCom.a"
	cd /Users/ralek/mocap-server/unix/protobuf && $(CMAKE_COMMAND) -P CMakeFiles/VRCom.dir/cmake_clean_target.cmake
	cd /Users/ralek/mocap-server/unix/protobuf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VRCom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
protobuf/CMakeFiles/VRCom.dir/build: /Users/ralek/mocap-server/bin/libVRCom.a

.PHONY : protobuf/CMakeFiles/VRCom.dir/build

protobuf/CMakeFiles/VRCom.dir/requires: protobuf/CMakeFiles/VRCom.dir/VRCom.pb.cc.o.requires

.PHONY : protobuf/CMakeFiles/VRCom.dir/requires

protobuf/CMakeFiles/VRCom.dir/clean:
	cd /Users/ralek/mocap-server/unix/protobuf && $(CMAKE_COMMAND) -P CMakeFiles/VRCom.dir/cmake_clean.cmake
.PHONY : protobuf/CMakeFiles/VRCom.dir/clean

protobuf/CMakeFiles/VRCom.dir/depend:
	cd /Users/ralek/mocap-server/unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ralek/mocap-server/src /Users/ralek/mocap-server/src/protobuf /Users/ralek/mocap-server/unix /Users/ralek/mocap-server/unix/protobuf /Users/ralek/mocap-server/unix/protobuf/CMakeFiles/VRCom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : protobuf/CMakeFiles/VRCom.dir/depend

