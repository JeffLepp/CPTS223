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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jeff/Desktop/Fall2024/CPTS223/PA2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jeff/Desktop/Fall2024/CPTS223/PA2/build

# Include any dependencies generated for this target.
include CMakeFiles/PA2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PA2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PA2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA2.dir/flags.make

CMakeFiles/PA2.dir/main.cpp.o: CMakeFiles/PA2.dir/flags.make
CMakeFiles/PA2.dir/main.cpp.o: ../main.cpp
CMakeFiles/PA2.dir/main.cpp.o: CMakeFiles/PA2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeff/Desktop/Fall2024/CPTS223/PA2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PA2.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PA2.dir/main.cpp.o -MF CMakeFiles/PA2.dir/main.cpp.o.d -o CMakeFiles/PA2.dir/main.cpp.o -c /home/jeff/Desktop/Fall2024/CPTS223/PA2/main.cpp

CMakeFiles/PA2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeff/Desktop/Fall2024/CPTS223/PA2/main.cpp > CMakeFiles/PA2.dir/main.cpp.i

CMakeFiles/PA2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeff/Desktop/Fall2024/CPTS223/PA2/main.cpp -o CMakeFiles/PA2.dir/main.cpp.s

CMakeFiles/PA2.dir/experimentFunctions.cpp.o: CMakeFiles/PA2.dir/flags.make
CMakeFiles/PA2.dir/experimentFunctions.cpp.o: ../experimentFunctions.cpp
CMakeFiles/PA2.dir/experimentFunctions.cpp.o: CMakeFiles/PA2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeff/Desktop/Fall2024/CPTS223/PA2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PA2.dir/experimentFunctions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PA2.dir/experimentFunctions.cpp.o -MF CMakeFiles/PA2.dir/experimentFunctions.cpp.o.d -o CMakeFiles/PA2.dir/experimentFunctions.cpp.o -c /home/jeff/Desktop/Fall2024/CPTS223/PA2/experimentFunctions.cpp

CMakeFiles/PA2.dir/experimentFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA2.dir/experimentFunctions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeff/Desktop/Fall2024/CPTS223/PA2/experimentFunctions.cpp > CMakeFiles/PA2.dir/experimentFunctions.cpp.i

CMakeFiles/PA2.dir/experimentFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA2.dir/experimentFunctions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeff/Desktop/Fall2024/CPTS223/PA2/experimentFunctions.cpp -o CMakeFiles/PA2.dir/experimentFunctions.cpp.s

# Object files for target PA2
PA2_OBJECTS = \
"CMakeFiles/PA2.dir/main.cpp.o" \
"CMakeFiles/PA2.dir/experimentFunctions.cpp.o"

# External object files for target PA2
PA2_EXTERNAL_OBJECTS =

PA2: CMakeFiles/PA2.dir/main.cpp.o
PA2: CMakeFiles/PA2.dir/experimentFunctions.cpp.o
PA2: CMakeFiles/PA2.dir/build.make
PA2: CMakeFiles/PA2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jeff/Desktop/Fall2024/CPTS223/PA2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PA2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA2.dir/build: PA2
.PHONY : CMakeFiles/PA2.dir/build

CMakeFiles/PA2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA2.dir/clean

CMakeFiles/PA2.dir/depend:
	cd /home/jeff/Desktop/Fall2024/CPTS223/PA2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jeff/Desktop/Fall2024/CPTS223/PA2 /home/jeff/Desktop/Fall2024/CPTS223/PA2 /home/jeff/Desktop/Fall2024/CPTS223/PA2/build /home/jeff/Desktop/Fall2024/CPTS223/PA2/build /home/jeff/Desktop/Fall2024/CPTS223/PA2/build/CMakeFiles/PA2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PA2.dir/depend

