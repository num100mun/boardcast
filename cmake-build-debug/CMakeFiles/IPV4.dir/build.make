# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1366/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1366/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/IPV4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/IPV4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IPV4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/IPV4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IPV4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IPV4.dir/flags.make

CMakeFiles/IPV4.dir/main.cpp.o: CMakeFiles/IPV4.dir/flags.make
CMakeFiles/IPV4.dir/main.cpp.o: /root/IPV4/main.cpp
CMakeFiles/IPV4.dir/main.cpp.o: CMakeFiles/IPV4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/IPV4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IPV4.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IPV4.dir/main.cpp.o -MF CMakeFiles/IPV4.dir/main.cpp.o.d -o CMakeFiles/IPV4.dir/main.cpp.o -c /root/IPV4/main.cpp

CMakeFiles/IPV4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/IPV4.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/IPV4/main.cpp > CMakeFiles/IPV4.dir/main.cpp.i

CMakeFiles/IPV4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/IPV4.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/IPV4/main.cpp -o CMakeFiles/IPV4.dir/main.cpp.s

# Object files for target IPV4
IPV4_OBJECTS = \
"CMakeFiles/IPV4.dir/main.cpp.o"

# External object files for target IPV4
IPV4_EXTERNAL_OBJECTS =

IPV4: CMakeFiles/IPV4.dir/main.cpp.o
IPV4: CMakeFiles/IPV4.dir/build.make
IPV4: CMakeFiles/IPV4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/root/IPV4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IPV4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IPV4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IPV4.dir/build: IPV4
.PHONY : CMakeFiles/IPV4.dir/build

CMakeFiles/IPV4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IPV4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IPV4.dir/clean

CMakeFiles/IPV4.dir/depend:
	cd /root/IPV4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/IPV4 /root/IPV4 /root/IPV4/cmake-build-debug /root/IPV4/cmake-build-debug /root/IPV4/cmake-build-debug/CMakeFiles/IPV4.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/IPV4.dir/depend

