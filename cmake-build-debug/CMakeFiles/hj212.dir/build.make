# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Work\git\HJ212

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Work\git\HJ212\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hj212.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hj212.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hj212.dir/flags.make

CMakeFiles/hj212.dir/src/main.c.obj: CMakeFiles/hj212.dir/flags.make
CMakeFiles/hj212.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Work\git\HJ212\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hj212.dir/src/main.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\hj212.dir\src\main.c.obj   -c D:\Work\git\HJ212\src\main.c

CMakeFiles/hj212.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hj212.dir/src/main.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Work\git\HJ212\src\main.c > CMakeFiles\hj212.dir\src\main.c.i

CMakeFiles/hj212.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hj212.dir/src/main.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Work\git\HJ212\src\main.c -o CMakeFiles\hj212.dir\src\main.c.s

CMakeFiles/hj212.dir/src/hj212.c.obj: CMakeFiles/hj212.dir/flags.make
CMakeFiles/hj212.dir/src/hj212.c.obj: ../src/hj212.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Work\git\HJ212\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hj212.dir/src/hj212.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\hj212.dir\src\hj212.c.obj   -c D:\Work\git\HJ212\src\hj212.c

CMakeFiles/hj212.dir/src/hj212.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hj212.dir/src/hj212.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Work\git\HJ212\src\hj212.c > CMakeFiles\hj212.dir\src\hj212.c.i

CMakeFiles/hj212.dir/src/hj212.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hj212.dir/src/hj212.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Work\git\HJ212\src\hj212.c -o CMakeFiles\hj212.dir\src\hj212.c.s

# Object files for target hj212
hj212_OBJECTS = \
"CMakeFiles/hj212.dir/src/main.c.obj" \
"CMakeFiles/hj212.dir/src/hj212.c.obj"

# External object files for target hj212
hj212_EXTERNAL_OBJECTS =

hj212.exe: CMakeFiles/hj212.dir/src/main.c.obj
hj212.exe: CMakeFiles/hj212.dir/src/hj212.c.obj
hj212.exe: CMakeFiles/hj212.dir/build.make
hj212.exe: CMakeFiles/hj212.dir/linklibs.rsp
hj212.exe: CMakeFiles/hj212.dir/objects1.rsp
hj212.exe: CMakeFiles/hj212.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Work\git\HJ212\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable hj212.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hj212.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hj212.dir/build: hj212.exe

.PHONY : CMakeFiles/hj212.dir/build

CMakeFiles/hj212.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hj212.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hj212.dir/clean

CMakeFiles/hj212.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Work\git\HJ212 D:\Work\git\HJ212 D:\Work\git\HJ212\cmake-build-debug D:\Work\git\HJ212\cmake-build-debug D:\Work\git\HJ212\cmake-build-debug\CMakeFiles\hj212.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hj212.dir/depend

