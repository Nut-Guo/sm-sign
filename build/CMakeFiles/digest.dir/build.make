# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build

# Include any dependencies generated for this target.
include CMakeFiles/digest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/digest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/digest.dir/flags.make

CMakeFiles/digest.dir/tools/digest.cc.o: CMakeFiles/digest.dir/flags.make
CMakeFiles/digest.dir/tools/digest.cc.o: ../tools/digest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/digest.dir/tools/digest.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/digest.dir/tools/digest.cc.o -c /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/tools/digest.cc

CMakeFiles/digest.dir/tools/digest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/digest.dir/tools/digest.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/tools/digest.cc > CMakeFiles/digest.dir/tools/digest.cc.i

CMakeFiles/digest.dir/tools/digest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/digest.dir/tools/digest.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/tools/digest.cc -o CMakeFiles/digest.dir/tools/digest.cc.s

CMakeFiles/digest.dir/utils/key.cc.o: CMakeFiles/digest.dir/flags.make
CMakeFiles/digest.dir/utils/key.cc.o: ../utils/key.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/digest.dir/utils/key.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/digest.dir/utils/key.cc.o -c /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/key.cc

CMakeFiles/digest.dir/utils/key.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/digest.dir/utils/key.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/key.cc > CMakeFiles/digest.dir/utils/key.cc.i

CMakeFiles/digest.dir/utils/key.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/digest.dir/utils/key.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/key.cc -o CMakeFiles/digest.dir/utils/key.cc.s

CMakeFiles/digest.dir/utils/sm.cc.o: CMakeFiles/digest.dir/flags.make
CMakeFiles/digest.dir/utils/sm.cc.o: ../utils/sm.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/digest.dir/utils/sm.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/digest.dir/utils/sm.cc.o -c /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/sm.cc

CMakeFiles/digest.dir/utils/sm.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/digest.dir/utils/sm.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/sm.cc > CMakeFiles/digest.dir/utils/sm.cc.i

CMakeFiles/digest.dir/utils/sm.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/digest.dir/utils/sm.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/utils/sm.cc -o CMakeFiles/digest.dir/utils/sm.cc.s

# Object files for target digest
digest_OBJECTS = \
"CMakeFiles/digest.dir/tools/digest.cc.o" \
"CMakeFiles/digest.dir/utils/key.cc.o" \
"CMakeFiles/digest.dir/utils/sm.cc.o"

# External object files for target digest
digest_EXTERNAL_OBJECTS =

digest: CMakeFiles/digest.dir/tools/digest.cc.o
digest: CMakeFiles/digest.dir/utils/key.cc.o
digest: CMakeFiles/digest.dir/utils/sm.cc.o
digest: CMakeFiles/digest.dir/build.make
digest: ../lib/openssl/libcrypto.so.1.1
digest: ../lib/openssl/libssl.so.1.1
digest: CMakeFiles/digest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable digest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/digest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/digest.dir/build: digest

.PHONY : CMakeFiles/digest.dir/build

CMakeFiles/digest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/digest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/digest.dir/clean

CMakeFiles/digest.dir/depend:
	cd /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build /mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/build/CMakeFiles/digest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/digest.dir/depend
