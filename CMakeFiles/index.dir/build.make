# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/singa/singa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/singa/singa/build

# Include any dependencies generated for this target.
include CMakeFiles/index.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/index.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/index.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/index.dir/flags.make

CMakeFiles/index.dir/src/main.cpp.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/src/main.cpp.o: CMakeFiles/index.dir/includes_CXX.rsp
CMakeFiles/index.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/index.dir/src/main.cpp.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/work/singa/singa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/index.dir/src/main.cpp.o"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/index.dir/src/main.cpp.o -MF CMakeFiles/index.dir/src/main.cpp.o.d -o CMakeFiles/index.dir/src/main.cpp.o -c /home/runner/work/singa/singa/src/main.cpp

CMakeFiles/index.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/src/main.cpp.i"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/singa/singa/src/main.cpp > CMakeFiles/index.dir/src/main.cpp.i

CMakeFiles/index.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/src/main.cpp.s"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/singa/singa/src/main.cpp -o CMakeFiles/index.dir/src/main.cpp.s

CMakeFiles/index.dir/src/model/model.cpp.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/src/model/model.cpp.o: CMakeFiles/index.dir/includes_CXX.rsp
CMakeFiles/index.dir/src/model/model.cpp.o: ../src/model/model.cpp
CMakeFiles/index.dir/src/model/model.cpp.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/work/singa/singa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/index.dir/src/model/model.cpp.o"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/index.dir/src/model/model.cpp.o -MF CMakeFiles/index.dir/src/model/model.cpp.o.d -o CMakeFiles/index.dir/src/model/model.cpp.o -c /home/runner/work/singa/singa/src/model/model.cpp

CMakeFiles/index.dir/src/model/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/src/model/model.cpp.i"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/singa/singa/src/model/model.cpp > CMakeFiles/index.dir/src/model/model.cpp.i

CMakeFiles/index.dir/src/model/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/src/model/model.cpp.s"
	/home/runner/work/_temp/e7430f71-2fd7-40b2-8303-078f5abdb4ff/emsdk-main/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/singa/singa/src/model/model.cpp -o CMakeFiles/index.dir/src/model/model.cpp.s

# Object files for target index
index_OBJECTS = \
"CMakeFiles/index.dir/src/main.cpp.o" \
"CMakeFiles/index.dir/src/model/model.cpp.o"

# External object files for target index
index_EXTERNAL_OBJECTS =

index.html: CMakeFiles/index.dir/src/main.cpp.o
index.html: CMakeFiles/index.dir/src/model/model.cpp.o
index.html: CMakeFiles/index.dir/build.make
index.html: external/sinen/libnen.a
index.html: CMakeFiles/index.dir/linklibs.rsp
index.html: CMakeFiles/index.dir/objects1.rsp
index.html: CMakeFiles/index.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/runner/work/singa/singa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable index.html"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/index.dir/build: index.html
.PHONY : CMakeFiles/index.dir/build

CMakeFiles/index.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean.cmake
.PHONY : CMakeFiles/index.dir/clean

CMakeFiles/index.dir/depend:
	cd /home/runner/work/singa/singa/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/singa/singa /home/runner/work/singa/singa /home/runner/work/singa/singa/build /home/runner/work/singa/singa/build /home/runner/work/singa/singa/build/CMakeFiles/index.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/index.dir/depend

