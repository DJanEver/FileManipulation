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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GROUP_WORK.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GROUP_WORK.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GROUP_WORK.dir/flags.make

CMakeFiles/GROUP_WORK.dir/main.c.obj: CMakeFiles/GROUP_WORK.dir/flags.make
CMakeFiles/GROUP_WORK.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/GROUP_WORK.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\GROUP_WORK.dir\main.c.obj   -c C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\main.c

CMakeFiles/GROUP_WORK.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GROUP_WORK.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\main.c > CMakeFiles\GROUP_WORK.dir\main.c.i

CMakeFiles/GROUP_WORK.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GROUP_WORK.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\main.c -o CMakeFiles\GROUP_WORK.dir\main.c.s

# Object files for target GROUP_WORK
GROUP_WORK_OBJECTS = \
"CMakeFiles/GROUP_WORK.dir/main.c.obj"

# External object files for target GROUP_WORK
GROUP_WORK_EXTERNAL_OBJECTS =

GROUP_WORK.exe: CMakeFiles/GROUP_WORK.dir/main.c.obj
GROUP_WORK.exe: CMakeFiles/GROUP_WORK.dir/build.make
GROUP_WORK.exe: CMakeFiles/GROUP_WORK.dir/linklibs.rsp
GROUP_WORK.exe: CMakeFiles/GROUP_WORK.dir/objects1.rsp
GROUP_WORK.exe: CMakeFiles/GROUP_WORK.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable GROUP_WORK.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GROUP_WORK.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GROUP_WORK.dir/build: GROUP_WORK.exe

.PHONY : CMakeFiles/GROUP_WORK.dir/build

CMakeFiles/GROUP_WORK.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GROUP_WORK.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GROUP_WORK.dir/clean

CMakeFiles/GROUP_WORK.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug C:\Users\hakee\Utech\Year1-Sem2\P2\GROUP_WORK\cmake-build-debug\CMakeFiles\GROUP_WORK.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GROUP_WORK.dir/depend

