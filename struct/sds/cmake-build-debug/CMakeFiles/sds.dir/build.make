# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/wendong/Desktop/clion-2018.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/wendong/Desktop/clion-2018.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wendong/CLionProjects/redis-learning/struct/sds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sds.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sds.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sds.dir/flags.make

CMakeFiles/sds.dir/sds.c.o: CMakeFiles/sds.dir/flags.make
CMakeFiles/sds.dir/sds.c.o: ../sds.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sds.dir/sds.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sds.dir/sds.c.o   -c /home/wendong/CLionProjects/redis-learning/struct/sds/sds.c

CMakeFiles/sds.dir/sds.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sds.dir/sds.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wendong/CLionProjects/redis-learning/struct/sds/sds.c > CMakeFiles/sds.dir/sds.c.i

CMakeFiles/sds.dir/sds.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sds.dir/sds.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wendong/CLionProjects/redis-learning/struct/sds/sds.c -o CMakeFiles/sds.dir/sds.c.s

CMakeFiles/sds.dir/sds.c.o.requires:

.PHONY : CMakeFiles/sds.dir/sds.c.o.requires

CMakeFiles/sds.dir/sds.c.o.provides: CMakeFiles/sds.dir/sds.c.o.requires
	$(MAKE) -f CMakeFiles/sds.dir/build.make CMakeFiles/sds.dir/sds.c.o.provides.build
.PHONY : CMakeFiles/sds.dir/sds.c.o.provides

CMakeFiles/sds.dir/sds.c.o.provides.build: CMakeFiles/sds.dir/sds.c.o


CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o: CMakeFiles/sds.dir/flags.make
CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o: /home/wendong/CLionProjects/redis-learning/gc/zmalloc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o   -c /home/wendong/CLionProjects/redis-learning/gc/zmalloc.c

CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wendong/CLionProjects/redis-learning/gc/zmalloc.c > CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.i

CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wendong/CLionProjects/redis-learning/gc/zmalloc.c -o CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.s

CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.requires:

.PHONY : CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.requires

CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.provides: CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.requires
	$(MAKE) -f CMakeFiles/sds.dir/build.make CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.provides.build
.PHONY : CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.provides

CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.provides.build: CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o


# Object files for target sds
sds_OBJECTS = \
"CMakeFiles/sds.dir/sds.c.o" \
"CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o"

# External object files for target sds
sds_EXTERNAL_OBJECTS =

sds: CMakeFiles/sds.dir/sds.c.o
sds: CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o
sds: CMakeFiles/sds.dir/build.make
sds: CMakeFiles/sds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable sds"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sds.dir/build: sds

.PHONY : CMakeFiles/sds.dir/build

CMakeFiles/sds.dir/requires: CMakeFiles/sds.dir/sds.c.o.requires
CMakeFiles/sds.dir/requires: CMakeFiles/sds.dir/home/wendong/CLionProjects/redis-learning/gc/zmalloc.c.o.requires

.PHONY : CMakeFiles/sds.dir/requires

CMakeFiles/sds.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sds.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sds.dir/clean

CMakeFiles/sds.dir/depend:
	cd /home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wendong/CLionProjects/redis-learning/struct/sds /home/wendong/CLionProjects/redis-learning/struct/sds /home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug /home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug /home/wendong/CLionProjects/redis-learning/struct/sds/cmake-build-debug/CMakeFiles/sds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sds.dir/depend
